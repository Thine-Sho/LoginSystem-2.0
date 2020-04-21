#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <map>

class assigner{
  private:

  public:
    void new(){
        for(auto &x: mymap){
          if(mymap.find(x.first) != mymap.end() ){
            vector<int>tmp = mymap[x.first];
            cout << x.first << ": ";
            for(auto &i: tmp){
              cout << i << ", ";
            }
            cout << endl;
          }
      }
    }
};
