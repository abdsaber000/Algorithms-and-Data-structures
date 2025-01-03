#include <bits/stdc++.h>
using namespace std;


template<typename T>
class MO{
protected:
    struct Query{
        int l , r , idx , block_idx;

        Query(int l , int r , int idx, int block_idx ) 
            : l(l) , r(r) , idx(idx) , block_idx(block_idx){}

        bool operator <(Query other) const{
            return (block_idx < other.block_idx) 
                || (block_idx == other.block_idx && r < other.r);
        }
    };

    vector<Query> queries;
    vector<T> answers;
    int block_size;

    virtual void add(int idx) = 0;

    virtual void erase(int idx) = 0;

    virtual T get_answer() = 0;

    void apply_MO(){
        answers = vector<T> (queries.size());
        sort(queries.begin() , queries.end());

        int cur_l = 0;
        int cur_r = -1;


        for(Query q: queries){
            while (cur_l > q.l) {
                cur_l--;
                add(cur_l);
            }

            while (cur_r < q.r) {
                cur_r++;
                add(cur_r);
            }

            while (cur_l < q.l) {
                erase(cur_l);
                cur_l++;
            }

            while (cur_r > q.r) {
                erase(cur_r);
                cur_r--;
            }
            
            answers[q.idx] = get_answer();
        }
    }
    
public:
    void add_query(int l , int r , int idx){
        queries.push_back(Query(l , r , idx, l / block_size));
    }

    vector<T> answer_queries(){
        apply_MO();
        return answers;
    }
};

class ModifiedMo : public MO<long long>{
    vector<int> fre;
    vector<int> arr;
    long long answer = 0;
    void add(int idx){
        answer -= 1LL * arr[idx] * fre[arr[idx]] * fre[arr[idx]];
        fre[arr[idx]]++;
        answer += 1LL * arr[idx] * fre[arr[idx]] * fre[arr[idx]];
    }

    void erase(int idx){
        answer -= 1LL * arr[idx] * fre[arr[idx]] * fre[arr[idx]];
        fre[arr[idx]]--;
        answer += 1LL * arr[idx] * fre[arr[idx]] * fre[arr[idx]];
    }

    long long get_answer(){
        return answer;
    }
public:
    ModifiedMo(vector<int> arr){
        
        this->arr = arr;
        this->fre = vector<int> ((int)1e6 + 9);
        this->block_size = sqrt(arr.size()) + 1;
    }


};


int main()
{
    int n , t;
    cin >> n >> t;
    vector<int> arr(n);
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    
   

    ModifiedMo mo(arr);


    for(int i = 0; i < t; i++){
        int l , r;
        cin >> l >> r;
        l--,r--;
        mo.add_query(l , r, i);
    }

    vector<long long> res = mo.answer_queries();

    for(auto x : res)
        cout << x << "\n";
}