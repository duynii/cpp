#include <iostream>
#include <cstring>
#include <queue>
#include <bits/types.h>
#include <cstdio>


using namespace std;

class Tree
{
    char    _c;
    Tree* _pleft;
    Tree* _pright;
public:
    Tree(char c, Tree* left=NULL, Tree* right=NULL) : _c(c),
        _pleft(left), _pright(right)
    {
    }

    virtual ~Tree() {
        if(_pleft) delete _pleft;
        if(_pright) delete _pright;
    }

    const Tree* getLeft() const { return _pleft; }
    const Tree* getRight() const { return _pright; }

    char getChar() const { return _c; }

    void breadth_first() 
    {
        queue<const Tree*> queue;

        queue.push(this);

        while(!queue.empty())
        {
            const Tree* node = queue.front();
            queue.pop();

            cout << node->getChar() << ' ';

            if(node->getLeft() != NULL) {
                queue.push(node->getLeft());
            } 

            if(node->getRight() != NULL) {
                queue.push(node->getRight());
            } 
        }
    }
};


int main(int argc, char* argv[])
{
    Tree* right4 = new Tree('d');
    Tree* left3 = new Tree('a', NULL, right4);
    Tree* right3 = new Tree('h', NULL, NULL);
    Tree* left2 = new Tree('f', left3, right3);
    Tree* right2 = new Tree('k', NULL, new Tree('z'));
    Tree root('j', left2, right2);

    root.breadth_first();
    return 0;
}
