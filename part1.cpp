#include <iostream>
#include <fstream>
using namespace std;

class counter
{
    private:
        class node
        {
            public:
                string data;
                node * left;
                node* right;
                int counter;
            
                node(string x)
                {
                    data = x;
                    counter = 1;
                    left = nullptr;
                    right = nullptr;
                }
        };

        node* root;

        //helper functions

        //recursive method to insert x given starting node pointer p
        void recInsert(string x, node*& p)
        {
            if(p==nullptr) //tree is empty
            {
                p = new node(x);
            }
            else
            {
                if(x < p->data)
                    recInsert(x, p->left);
                else
                    recInsert(x, p->right);
            }
        }

        //recursive method to find string d given the starting node pointer p
        node* recFind(string d, node *p)
        {
            if(p == nullptr) //nothing
            {
                return nullptr;
            }
            else if(d == p->data)
            {
                return p;
            }
            else
            {                
                node * left = recFind(d, p->left);
                node * right = recFind(d, p->right);

                if(right != nullptr)
                    return right;
                else 
                    return left;
            }
        }
        
        void print(node* p)
        {
            if(p!= nullptr)
            {

                print(p->left);
                cout << p->data << ": " << p->counter << endl;
                print(p->right);
                
            }
            else
            {
                return;
            }
        }

        void write(node* p, fstream& w)
        {
            if(p!= nullptr)
            {

                write(p->left, w);
                w << p->data << ": " << p->counter << endl;
                write(p->right, w);
                
            }
            else
            {
                return;
            }
        }

    public:

        counter()
        {
            root = nullptr;
        }

        void insert(string d)
        {
            //check if there is a node that exists
            node* p = find(d);
            if(p == nullptr) // does not exist yet
                recInsert(d, root);
            else
                p->counter += 1;
        }

        node* find(string d)
        {
            return recFind(d, root);
        }

        void print()
        {
            print(root);
        }

        void write(fstream& w)
        {
            write(root, w);
        }
};

int main()
{
    //initialize and declare variables
    fstream read;
    fstream write;
    read.open("story.txt", fstream::in);
    write.open("wordCounts.txt", fstream::out);
    counter words;

    //get data from file
    string in;
    while(read >> in)
    {
        words.insert(in);

        //safekeeping
        in = "";
    }

    //write the data to the file
    words.write(write);

    //take care of fstream
    read.close();
    write.close();

    return 0;
}