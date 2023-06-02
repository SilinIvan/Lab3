#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <chrono>
#include <iterator>
#include <algorithm>
#include <map>
#include <set>

using namespace std;
int meth=1;
long long hashFunctionSimple(string str) {
    int hash = 0;
    for (char c : str) {
        hash += c;
    }
    return hash;
}

long long hashFunctionComplicated(string str) {
    int hash = 5381;
    for (char c : str) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

struct housing_estate {
    int numberHouse;
    int numberApartment;
    int number_of_rooms;
    float square;
    string name;
    int number_of_residents;
    int hash; // добавляем поле hash

    housing_estate() {};

    housing_estate(int numberHouse, int numberApartment, float square, string name) {
        this->numberHouse = numberHouse;
        this->numberApartment = numberApartment;
        this->square = square;
        this->name = name;
        if( meth == 1){
          this->hash = hashFunctionSimple(this->name); // вычисляем хэш и сохраняем его в поле hash
        }
       if( meth == 2){
        this->hash = hashFunctionComplicated(name); // вычисляем хэш и сохраняем его в поле hash
        }
    }


    bool operator > ( housing_estate& h2)
    {
        if (this->name==h2.name) {
                            return true;
        }
        else{


        int ans = this->name.compare(h2.name);
                    return ans > 0;
       }
    };

    bool operator >= ( housing_estate& h2)
    {
        if (this->name==h2.name) {
                            return true;
        }
        else{


        int ans = this->name.compare(h2.name);
                    return ans >= 0;
       }
    };
    bool operator < ( housing_estate& h2)
    {
        if (this->name==h2.name) {
                            return true;
        }
        else{


        int ans = this->name.compare(h2.name);
                    return ans < 0;
       }
    };
    bool operator <= ( housing_estate& h2)
    {
        if (this->name==h2.name) {
                            return true;
        }
        else{
        int ans = this->name.compare(h2.name);
                    return ans <= 0;
       }
    };

};
std::ostream& operator << (std::ostream &os, const housing_estate &h)
{
    return os << h.numberHouse << "," << h.numberApartment << "," << h.number_of_rooms << "," << h.square << "," << h.name << "," << h.number_of_residents ;
}
template <class T> std::vector<int> LinearSearch (vector<T>& a, int size, string key)
{
   std::vector<int> vec(size/2);
   for(int i=0;i<size;i++){
       if(a[i].name == key){
           vec.push_back(i);
       }
     }
   if(vec.empty()){
       vec.push_back(-1);
   }
  else return vec;
}
template<class T> int partition(vector<T>& nums, int low, int high)
{
int i = low - 1;
//choosing pivot as last element
T pivot = nums[high];
for (int j = low; j < high; j++)
{
if (nums[j] <= pivot)
{
i++;
swap(nums[i], nums[j]);
}
}
swap(nums[i + 1], nums[high]);
return i + 1;
}
template<class T> void quickSort(vector<T>& nums, int low, int high)
{
if (low < high)
{
int pivot = partition(nums, low, high);
quickSort(nums, low, pivot - 1);
quickSort(nums, pivot + 1, high);

}
}
template <class T> std::pair<int,int> BinSearch( vector<T> a,  string key,  int low, int high)
{
    //НАДО Вернуть две границы
    int f=0;
         if ( low > high )
         {
              return std::make_pair(-1,0);
         }
         int mid = ( low + high ) / 2;
         if (  a[mid].name == key && f==0 ){
             f=mid;
         }
         if(a[mid].name != key && a[mid-1].name == key){
            return std::make_pair(f,mid-1);
         }
         else if (f!=0){
             return std::make_pair(f,f);
         }
         if ( a[mid].name < key){
            BinSearch(a,key,mid+1,high);
         }
         if ( a[mid].name > key ){

            BinSearch(a,key,low,mid-1);
         }
}
//class HashTable
//{
//public:
//    HashTable() {}
//    HashTable(const int a) : algo(a) {}
//    void addElement(housing_estate& object)
//    {
//        data.insert(pair<long long, housing_estate>(curHash(object), object));
//    }
//    int countCollisions() const
//    {
//        auto p0 = data.begin();
//        set<long long> myset;
//        while (p0 != data.end()) {
//            myset.insert(p0->first);
//            ++p0;
//        }
//        return data.size() - myset.size();
//    }

//    void findElement(string& name) const
//    {
//        //first - lower bound, second - upper bounds
//        pair<multimap<long long, housing_estate>::const_iterator, multimap<long long, housing_estate>::const_iterator> p1;
//        p1 = data.equal_range(curHash(name));
//        while (p1.first != p1.second) {
//            p1.first++;
//        }
//    }

//    long long curHash(const housing_estate& object) const
//    {
//        return object.hash;
//    }

//    long long curHash(string& name) const
//    {
//        if (meth == 1)
//        {
//            return hashFunctionSimple(name);
//        }
//        else
//        {
//            return hashFunctionComplicated(name);
//        }
//    }
//private:
//    multimap<long long, housing_estate> data;
//    int algo = 0;
//    int collisions = 0;
//};
class HousingEstateHashTable {
public:
    HousingEstateHashTable() {}
    HousingEstateHashTable(const int a) : algo(a) {}
    void addElement(housing_estate& object) {
        data.insert(std::make_pair(curHash(object), object));
    }
    int countCollisions() const {
        std::set<long long> myset;
        for (const auto& p : data) {
            myset.insert(p.first);
        }
        return data.size() - myset.size();
    }
    void findElement(const std::string& name) const {
        long long hash_val = curHash(name);
        auto it = data.find(hash_val);
        if (it != data.end()) {
            while (it != data.upper_bound(hash_val)) {
                if (it->second.name == name) {
                    return;
                }
                it++;
            }
        }
    }


    long long curHash(const housing_estate& object) const {
        return object.hash;
    }
    long long curHash(const std::string& name) const {
        if (meth == 1)
        {
            return hashFunctionSimple(name);
        }
        else
        {
            return hashFunctionComplicated(name);
        }
    }
private:
    std::multimap<long long, housing_estate> data;
    int algo = 0;
};


void File(string file,int method, string key) {
        meth= method;
        string path = "C:/Users/Ivan/"+file;
        ifstream f(path);
        string l;
        string fi;
        vector<housing_estate> dannie;
        while ( getline(f,l) )    // get next line in file
        {
            stringstream ss(l);
            int i = 0;
            string name1;
            int numberHouse,number_of_rooms,number_of_residents;
            float square;
            int numberApartment;
            while (getline(ss,fi,','))
            {
                if(i==0){
                 name1 = fi;
                }
                if(i==1){
                    square = stof(fi);
                }
                if(i==2){
                    numberHouse = stoi(fi);
                }
                if(i==3){
                    numberApartment = stoi(fi);
                }

                ++i;
             }
             housing_estate house(numberHouse,numberApartment,square,name1);
            dannie.push_back(house);
        }
        HousingEstateHashTable hTable(meth);
        for (int i = 0; i < dannie.size(); i++) {
            hTable.addElement(dannie[i]);
        }
        auto begin = std::chrono::steady_clock::now();
        hTable.findElement(key);
        auto end = chrono::steady_clock::now();
        auto elapsed_ms = chrono::duration_cast<chrono::nanoseconds>(end - begin);
        cout << dannie.size() << "\t" << elapsed_ms.count() << endl;
//        cout << dannie.size() << "\t" << hTable.countCollisions() << endl;

    }

int main() {

    cout<<"Simple"<<std::endl;
   File("200.txt",1,"dpftfx hmvpzdg hciqjb");
   File("1000.txt",1,"gtxqdy nunwti uifeyrezmy");
   File("2000.txt",1,"vtpqqp pfqsterl rtvnwwz");
   File("10000.txt",1,"knjafstgt ncnnfyfnoos fcojggh");
   File("20000.txt",1,"tkvlpezm rxrmghrzrtw miycxz");
   File("100000.txt",1,"pcounimo eudeljnxs zsvxmdr");
   File("150000.txt",1,"xfyqkrxtsh pjblbesa dowbzfa");
   cout<<"Complex"<<std::endl;
   File("200.txt",2,"dpftfx hmvpzdg hciqjb");
   File("1000.txt",2,"gtxqdy nunwti uifeyrezmy");
   File("2000.txt",2,"vtpqqp pfqsterl rtvnwwz");
   File("10000.txt",1,"knjafstgt ncnnfyfnoos fcojggh");
   File("20000.txt",2,"tkvlpezm rxrmghrzrtw miycxz");
   File("100000.txt",2,"umhfituzjj vpdnqylkko ijocxzndwsq");
   File("150000.txt",2,"qvammpwj ubbnnttbv cmvjzhac");


   cout<<"  "<<endl;
}
