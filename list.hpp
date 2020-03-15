#include <iostream>

using namespace std;
namespace sebas{

template <class T>
class nodel {
	public:
		T info;
		nodel<T> *next;
};

template <class T>
class list {
 	nodel<T> *pFirst;
 	int n;
  	public:
	  	typedef nodel<T> *pos;
    	list(){
    		n = 0;
    		pFirst = NULL;
		}
		~list(){
    		nodel<T> *pTemp;
   			while(pFirst != NULL){
        		pTemp = pFirst;
       			pFirst = pFirst->next;
        		delete pTemp;
    		}
		}
		bool isEmpty(){
    		return pFirst == NULL;
		}
		pos first(){
			return pFirst;
		}
		pos last(){
			return NULL;
		}
		void next(pos &pValue){
			if (pValue != NULL)
			pValue = pValue->next;
		}
		T* get(pos pValue){
			if (pValue != NULL)
				return &(pValue->info);
			return NULL;
		}
    	void insert(T &x, pos pValue){
			nodel<T> *pNew = new nodel<T>();
			pNew->info = x;
			pNew->next = pValue;
			if (pFirst == NULL || pValue == pFirst)
				pFirst = pNew;
			else{
				nodel<T> *pTemp = pFirst;
				while(pTemp->next != pValue)
					pTemp = pTemp->next;
				pTemp->next = pNew;
			}
			n++;
		}
		void insert(const T &x, pos pValue){
			nodel<T> *pNew = new nodel<T>();
			pNew->info = x;
			pNew->next = pValue;
			if (pFirst == NULL || pValue == pFirst)
				pFirst = pNew;
			else{
				nodel<T> *pTemp = pFirst;
				while(pTemp->next != pValue)
					pTemp = pTemp->next;
				pTemp->next = pNew;
			}
			n++;
		}
		void erase(pos pValue){
			if (pValue == pFirst)
				pFirst = pFirst->next;
			else{
				nodel<T> *pTemp = pFirst;
				while(pTemp->next != pValue)
					pTemp = pTemp->next;
				pTemp->next = pValue->next;
			}
			delete pValue;
			n--;
		}
		int size(){
    		return n;
		}
		void print(){
			cout<<"lista: "<<endl;
			nodel<T> *pTemp = pFirst;
			while(pTemp->next!= NULL){
				cout<<pTemp->info<<endl;
				pTemp=pTemp->next;
			}
			if(pTemp->next==NULL)
				cout<<pTemp->info<<endl;

			if(pTemp==NULL)
				cout<<"empty"<<endl;

		}
};

template <class T>
class stack:public list<T>{
	public:
	stack(){
	}
	~stack(){
	}
	bool isEmpty(){
		return list<T>::isEmpty();
	}
	void push(T&x){
		list<T>::insert(x,list<T>::first());
	}
	void pop(){
		list<T>::erase(list<T>::first());
	}
	int size(){
		return list<T>::size();
	}
	T* top(){
		return list<T>::get(list<T>::first());
	}
	void print(){
		list<T>::print();
	}
};

template<class T>
class queue:public list<T>{
	public:
	queue(){
	}
	~queue(){
	}
	bool isEmpty(){
		return list<T>::isEmpty();
	}
	void enqueue(T&x){
		list<T>::insert(x, list<T>::last());
	}
	void dequeue(){
		list<T>::erase(list<T>::first());
	}
	int size(){
		return list<T>::size();
	}
	T* head(){
		return list<T>::get(list<T>::first());
	}
	void print(){
		list<T>::print();
	}
};

template <class T>
class dipolo:public list<T>{
	public:
	dipolo(){
	}
	~dipolo(){
	}
	bool isEmpty(){
		return list<T>::isEmpty();
	}
	void insertFirst(T&x){
		list<T>::insert(x,list<T>::first());
	}
	void insertLast(T&x){
		list<T>::insert(x,list<T>::last());
	}
	void erasefirst(){
		list<T>::erase(list<T>::first());
	}
	void eraselast(){
		list<T>::erase(list<T>::last());
	}
	int size(){
		return list<T>::size();
	}
	T* first(){
		return list<T>::get(list<T>::first());
	}
	T* last(){
		return list<T>::get(list<T>::last());
	}
};
}
