#include<bits/stdc++.h>
using namespace std;

template<typename T>
class AVLTree{
private:

    struct Node{
        T val ;
        int height {};
        Node* left = nullptr;
        Node* right = nullptr;

        Node(T val) : val(val){}

        int child_height(Node *node){
            if(!node)
                return -1;
            return node->height;
        }

        int update_height(){
            return height = 1 + max(child_height(left) , child_height(right));
        }

        int balance_factor(){
            return child_height(left) - child_height(right);
        }  
    };

    Node *root = nullptr;

    Node* right_rotation(Node *Q){
        Node *P = Q->left;
        Q->left = P->right;
        P->right = Q;
        P->update_height();
        Q->update_height();
        return P;
    }

    Node* left_rotation(Node *P){
        Node* Q = P->right;
        P->right = Q->left;
        Q->left = P;
        P->update_height();
        Q->update_height();
        return Q;
    }

    /*
        left > right (bf > 0) ==> rotate right
        left < right (bf < 0) ==> rotate left
    */

    Node* balance(Node *node){
        if(node->balance_factor() == 2){ 
            if(node->left->balance_factor() == -1) 
                node->left = left_rotation(node->left);
            node = right_rotation(node);
        }else if(node->balance_factor() == -2){ 
            if(node->right->balance_factor() == 1) 
                node->right = right_rotation(node->right);
            node = left_rotation(node);
        }
        return node;
    }

    Node* insert_node(T target, Node* node){
        if(target < node->val){
            if(!node->left)
                node->left = new Node(target);
            else
                insert_node(target , node->left);
        }else if(target >= node->val){
            if(!node->right)
                node->right = new Node(target);
            else
                insert_node(target , node->right);
        }
        node->update_height();
        return balance(node);
    }

    Node* get_minimum_node(Node* node){
        while(node && node->left)
            node = node->left;
        return node;
    }

    Node* delete_node(T target , Node *node){
        if(!node)
            return nullptr;

        if(target < node->val)
            node->left = delete_node(target , node->left);
        else if(target > node->val)
            node->right = delete_node(target , node->right);
        else{
            Node* temp = node;

            if(!node->right && !node->left)
                node = nullptr;
            else if(!node->right)
                node = node->left;
            else if(!node->left)
                node = node->right;
            else{

                /*The smallest node that's greater than the largest node 
                    in left subtree */

                Node* minimum_node = get_minimum_node(node->right);

                node->val = minimum_node->val;
                node->right = delete_node(node->val , node->right);

                temp = nullptr;
            }

            if(temp){
                delete temp;
            }
        }

        if(node){
            node->update_height();
            node = balance(node);
        }
        return node;
    }

    int count_value(T target , Node* node){
        if(!node)
            return 0;
        int ans = 0;
        if(node->val == target)
            ans++;
        
        if(target >= node->val){
            ans += count_value(target , node->right);
        }else{
            ans += count_value(target , node->left);
        }
        return ans;

    }

    pair<bool, T> minimize_bound(pair<bool, T> & current, pair<bool,T> target){
        auto result = current;
        if(target.first){
            if(current.first){
                if(target.second < current.second)
                    result = target;
            }else{
                result = target;
            }
        }
        return result;
    }

    pair<bool, T> bound_value(T target , Node* node, bool is_lower_bound){
        if(!node)
            return {false , target};
        
        pair<bool, T> result = {false , target};

        bool is_valid_value = is_lower_bound ? target <= node->val : target < node->val;
        if(is_valid_value){
            result = {true, node->val};
            result = minimize_bound(result , 
                bound_value(target , node->left , is_lower_bound));
        }else{
            result = minimize_bound(result , 
                bound_value(target , node->right , is_lower_bound));
        }

        return result;
    }


public:
    void insert(T target){
        if(!root)
            root = new Node(target);
        else
            root = insert_node(target , root);
    }

    void erase(T target){
        if(root)
            root = delete_node(target , root);
    }

    int count(T target){
        return count_value(target , root);
    }

    /*if the value exits, the first will be true.*/
    pair<bool, T> lower_bound(T target){
        return bound_value(target, root , true);
    }

    pair<bool, T> upper_bound(T target){
        return bound_value(target , root, false);
    }
};

int main(){
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(11);
    tree.insert(12);
    tree.insert(12);
    cout << tree.count(12) << "\n";
    tree.erase(12);
    cout << tree.count(12) << "\n";

    tree.erase(12);
    cout << tree.count(12) << "\n";

    tree.erase(12);
    cout << tree.count(12) << "\n";

    tree.insert(14);

    auto result = tree.lower_bound(11);

    cout << result.first << " " << result.second << " ~~\n";

    result = tree.upper_bound(11);

    cout << result.first << " " << result.second << " ~~\n";

    AVLTree<string> st;
    st.insert("abdo");
    st.insert("saber");

    st.insert("abdo");

    cout << st.count("abdo") << "\n";
    return 0;
}