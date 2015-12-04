class mycomparison
{
    bool reverse;
public:
    mycomparison(const bool& revparam=false)
    {reverse=revparam;}
    bool operator() (const pair<int, int>& lhs, const pair<int, int>&rhs) const
    {
        if (reverse) return (lhs.first<rhs.first);
        else return (lhs.first>rhs.first);
    }
};


class Solution {
public:
    vector<int> result;
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparison > heap;
        
        vector<int> f(1, 1);
        for (int i = 0; i < primes.size(); i++) {
            heap.push(pair<int, int>(primes[i], 0));
        }
 
        int curIndex = 0;
        int curNum = 0;
        
        while(f.size() < n) {
            curNum = heap.top().first;
            curIndex = heap.top().second;
            heap.pop();
            
            if (curNum > f[f.size()-1]) {
                f.push_back(curNum);
            }
            
 
            int prime = curNum / f[curIndex];
            int nextIndex = curIndex + 1;
            int nextNum = prime * f[nextIndex];
            heap.push(pair<int, int>(nextNum, nextIndex));  
            
        }
        
        return f[n-1];
    }
};
