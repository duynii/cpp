#include <regex.h>
#include <string>
#include <algorithm>
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <cstdio>

using namespace std;

// Hexadecimal ANCII value to ANCII char
//  we can also use a map<string, char> thats initialised once - more memory for speed.
inline char hex_to_char(const string& hex) {
    int val;
    sscanf(hex.c_str(), "%i", &val);
    return char(val);
}

static const int c_max_matches = 20;

// List of pair of substrings inside the URL, the ones matched by regex or need to be removed
typedef pair<size_t, size_t> pair_delete;
typedef list<pair_delete> list_deletes;

// Using regex.h extended regular expression
//  find the matches in 'regexp' specified and add the matches to the 'list'
int find_matches(const string& url, const char* regexp, 
                        list_deletes& list)
{
    regex_t exp; //Our compiled expression, extended reg. expression and case insensitive match
    int ret = regcomp(&exp, regexp, REG_EXTENDED | REG_ICASE);

    if(ret != 0) {
        cerr  << "Failed to compile regular expression" << endl;
        return 1;
    }

    regmatch_t matches[c_max_matches]; //A list of the matches in the string
    if (regexec(&exp, url.c_str(), c_max_matches, matches, 0) == 0) 
    {
        for(int i=0; matches[i].rm_so != -1 && i<c_max_matches; ++i) {
            ///cout << "matched: " << url.substr(matches[i].rm_so, matches[i].rm_eo - matches[i].rm_so) << endl;
            // Pushes the substring matches - index pair - start of match index and end
            list.push_back( pair_delete(matches[i].rm_so, matches[i].rm_eo - 1) ); 
        }
    }
    return 0;
}

/** 
* Go through url once, url is modified to remove all substrings inside 'deletes'
*  which are just pair of indexes specifying the internal substrings.
*/
void remove_deletes(string& url, const list_deletes& deletes)
{
    ostringstream new_url;
    size_t start_pos = 0; //start position to crawl through url
    for(list_deletes::const_iterator ipair=deletes.begin(); ipair!=deletes.end(); ++ipair) 
    {
        
        // Append url to new_url up to the match
        for(size_t j=start_pos; j<ipair->first; ++j) {
            new_url << url[j];
        }
        if((ipair->second + 1) > start_pos)
            start_pos = ipair->second + 1; // starts after the matched substring
    }
    // Add the last un-matched part of origial url  
    for(size_t j=start_pos; j<url.size(); ++j) {
        new_url << url[j];
    }
    url = new_url.str();
}

// C like function to go through the url once
//  replaces percent encoding if needed.
//  replaces anything/.. 
//  replaces // with / 
//  replaces /./ with '/'
// Until STL regex library is robust and provides regex greping functionality, C is used.
void clean_hex_and_slashes(string& url)
{
    // Find any % or /, maybe better to look for '/' only
    size_t index = url.find_first_of("/%");
    size_t last_slash = index;
    // last index of the match
    size_t index_end = index; 
    size_t start = 0;
    ostringstream ss;
    while(index != string::npos && index < url.size())
    {
        string append;
        if(url[index] == '%')  //TBC change to inner loop parsing a cannonical part of URL
        {
            // replace percent encoded character
            index_end = index + 2; // Two more hex
            // Transcode 
            char a = url[index+1];
            char b = url[index+2];
            char c = hex_to_char(string("0x") + a + b);
            if( (c >= 'A' && c <= 'Z') || (c <= 'a' && c >= 'b') || 
                (c >= '0' && c <= '9') || c == '-' || c == '.' || c == '_' || c == '~') {
                append = c; // This is the character decoded
            } 
            else {
                // else we dont care to decode
                append = url.substr(index, index_end - index + 1);
            }
        }
        else 
        {

            if(url[index+1] == '/') //replace '//'
            {
                index_end = index + 1; // delete first '/'
            }
            else if(url[index+1] == '.') // Check for '/.'
            {
                // Check for '/..'
                if((index+2) < url.size() && url[index+2] == '.') {
                    index_end = index + 2;
                    index = last_slash; // remove anything before /.. eg. 'this/..'
                }
                else { // '/.'
                    index_end = index + 1;
                }
            }
            else { // Just a normal singular '/'
                index_end = index;
                append = '/';
            }   

            last_slash = index;
        }

        //Copy part of string that didnt match
        for(size_t i=start; i<index; ++i) {
            ss << url[i];
        }
        if(!append.empty()) ss << append;

        // Starts after last match
        start = index_end + 1;

        // Find again
        index = url.find_first_of("/%", start);
    }
    //Copy end part of string that didnt match
    for(size_t i=start; i<url.size(); ++i) {
        ss << url[i];
    }

    url = ss.str();
}

string clean_url(const string& in)
{
    string url = in;

    // Assumptions:
    //  query params starting with '&' are not wanted
    //  'www.' before the domain name is not needed, so www.example.com becomes example.com
    list_deletes matches;
    list_deletes temp;
    // Regex pass through, this long expression can be broken up 
    //  regex looking from start of string
    find_matches(url, "(^https?://)((www\\.)*)?", matches);
    if(!matches.empty()) {
        matches.pop_front(); //Front match is the whole regex not substrings
    }
    // Find default ports, if default port is always present this regex can be combined with above
    //  It does not support "(:80|433)?"
    find_matches(url, "(:80|:443)", temp);
    matches.insert(matches.end(), ++(temp.begin()), temp.end());
    temp.clear();

    // Regex looking from end of string
    // For the query parameters, another option would be
    //  to find the first ';', '?', '&' or '#' char and remove the last part of the string.
    find_matches(url, "(/default|/index)(\\.)(asp|html|htm|php|aspx)(;[a-z0-9=]*)(\\?[a-z0-9=]*)((&[a-z0-9=]+)*(#[a-z0-9]+))$", temp);
    matches.insert(matches.end(), ++(temp.begin()), temp.end());
    temp.clear();

    // Remove substring matches above, pass through to remove unwanted sub-strings
    remove_deletes(url, matches);

    ///cout << "1: " << url  << endl;

    // Transcode percent-encoding, removes '//', 'previous/..' and '/./'
    //  one pass
    clean_hex_and_slashes(url);
    // Remove trailing slash
    if(!url.empty() && url[url.size()-1] == '/') {
        url = url.substr(0, url.size()-1);
    }
    // Transform what is left to lower case.
    std::transform(url.begin(), url.end(), url.begin(), ::tolower);
    return url;
}

