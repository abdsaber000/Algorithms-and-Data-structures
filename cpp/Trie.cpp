#include <bits/stdc++.h>

using namespace std;

class Trie{
private:
    static const int MAX_CHILDES = 26;
    Trie* child[MAX_CHILDES] = {};
    bool isLeaf {};

    void _insert(const string & str){
        
        Trie* current = this;

        for(auto x : str){
            int ch = x - 'a';
            if(!current->child[ch])
                current->child[ch] = new Trie();

            current = current->child[ch];
        }
        current->isLeaf = true;
    }

    bool _exist(const string & str){
        Trie* current = this;

        for(auto x : str){
            int ch = x - 'a';
            if(!current->child[ch])
                return false;

            current = current->child[ch];
        }
        return current->isLeaf;
    }
    string longest_common_prefix()
public:
    Trie(){
        memset(child , 0, sizeof(child));
    }

    void insert(const string & str){
        _insert(str);
    }

    bool exist(const string &str){
        return _exist(str);
    }
};

int main(){

    Trie t;
    t.insert("abdo");
    t.insert("saber");
    t.insert("abd");

    cout << t.exist("abdo") << " " << t.exist("abu") << "\n";
    return 0;
}