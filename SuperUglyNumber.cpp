class Solution {
public:
    vector<int> result;
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        priority_queue<int, vector<int>, greater<int> > heap;
        heap.push(1);
        int curIndex = 0;
        int curNum = 0;
        
        while(curIndex < n) {
            while(curNum == heap.top()) {
                heap.pop();
            }
            curNum = heap.top(); heap.pop();
            for(int i = 0; i < primes.size(); i++) {
                heap.push(primes[i] * curNum);
            }
            curIndex++;
            
        }
        
        return curNum;
    }
};
