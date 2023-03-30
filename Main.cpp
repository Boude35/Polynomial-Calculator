#include <iostream>	
#include <fstream>
#include <string>
#include<list>

#include "Term.hpp"

using namespace std;


//put the degrees in descending order
void ordenar(list<Term> &list)
{
	list.sort();	
}

//add values with the same degree
void addition(list<Term> &list)
{
	ordenar(list); //put the polynomial in order
	std::list<Term> second;//new list
	int suma=0;//accumulate the coefficient when adding few polinomyals
	std::list<Term>::iterator i;//iterator to control de loop
	for(i = list.begin(); i != list.end(); i++)//go over all the values;
	{
		if(i -> degree() == next(i,1)-> degree())//if the degrees are the same
		{
			suma += i->coefficient();//add it to sum

		}
		else if(suma)// if the degrees are differente and suma exist
		{
			//add the last value
			suma += i -> coefficient();
			//new term
			Term h;
			h.coefficient() = suma;
			h.degree() = i-> degree();
			//reestart sum
			suma = 0;
			//add it to the list
			second.push_back(h);
		}
		else //if none of the previous
		{
			second.push_back(*i);//add the values to the list

		}
	}
	
	
	list = second;//copy the list
	
}

// print all the values in the list
void print(list<Term> &list)
{
	ordenar(list);
	addition(list);
	bool sign = true;//to print the first sign
	for(Term t: list) //go over all the values
	{	
		if(t.coefficient()>0 )//if the coeff is bigger than 0
		{
			if (sign == true)//and sign 0 true
			{
				cout<< t;
				sign = false;
			}
			else cout<< "+" << t;
		}
		else if (t.coefficient()<0)//else if coeff is less than 0
			cout<<t;
	}
	cout<<endl;
}

//read the values
void read(list<Term>& list)
{
	Term t;//declare a term
	cin >> t; //read it
	//while there are terms different from 0
	while(t.coefficient() != 0)
	{		
		list.push_back(t);
		cin>>t;
	}
}


//evaluate the polynomio for a given number
void evaluation(list<Term> list)
{	
	addition(list);//add the values with same degree
	ordenar(list);//put in order of degree
	std::list<Term> second;//new list
	float numero;//user prompt
	int sum;//sum horner
	int difference;//difference between higher and lower degree
	cin>>numero;
	sum = 0;//inizialize sum
	std::list<Term>::iterator i;//iterator to control the lop
	
	//go over all the values in the ñist
	for(i = list.begin(); i != list.end() ; i++)
	{
		difference = i->degree() - next(i,1)->degree();//take the difference
		
		while(difference >=2)//add missinf terms
		{
			Term t(0, next(i,1)->degree() + (difference-1));
			second.push_front(t);
			difference--;
			
		}

		
	}
	//merge both list
	list.merge(second);
	//ordenate it
	ordenar(list);
	//go over the list
	for(Term t: list)
	{   
			sum = sum * numero + t.coefficient();

	}
	
	cout<< sum <<endl;
}

//merge two different polynomios
void add(list<Term> &list)
{
	std::list<Term> second;//create a new list
	second = {0};//give it the value 0
	read(second); // read all the values
	
	list.merge(second);// merge both
}

//merge the values of two list changin the sign
void substraction(list<Term> &list)
{
	std::list<Term> second;//new list
	Term t;
	cin >> t;//read values
	while(t.coefficient() != 0)
	{	
		t.coefficient()*= -1;	//change the sign cause the are substracting
		list.push_front(t); // add it to the list
		cin>>t; // next value
	}
	
	list.merge(second);// merge both
}


//multiplicate values
void multiplication(list<Term> &list)
{
	std::list<Term> second;//other polynomio
	std::list<Term> third;
	second = {0};
	read(second);//read the values
	
	for(Term x: second)//go through all the values of list
	{
		for(Term t: list)//go through all the values of second
		{
			if(t.coefficient() != 0 && x.coefficient() != 0)
			{
				t.coefficient() = t.coefficient() * x.coefficient();
				t.degree() = t.degree() + x.degree();
				third.push_back(t);
				
			}
		}
	}
	list = third;
}


int main(int argc, char *arv[])
{
	list<Term> poly = {0};//new poynomi equal 0
	char prompt;// controller
	
	
	cout<<"Welcome To PolyCalc!"<<endl;
	do// ask continiuly for a promp until it is equal to q
	{
	cout<< ">>> ";
	cin>> prompt;
	switch(prompt)
	{
		
		case 'c'://clear polynomio
			poly = {0};
			cout << "Acumulator= ";
			print(poly);
			break;
		case 's'://add new polynomio
			poly = {0};
			read(poly);
			cout << "Acumulator= ";
			print(poly);
			break;
		case 'e'://evaluate polynomio
			evaluation(poly);
			break;
		case '+'://add a value
			add(poly);
			cout << "Acumulator= ";
			print(poly);
			break;
		case '-'://suvstract a value
			substraction(poly);
			cout << "Acumulator= ";
			print(poly);
			break;
		case '*'://multiplication
			multiplication(poly);
			cout << "Acumulator= ";
			//addition(poly);
			print(poly);
			break;
		case 'p'://print it
			print(poly);
				
			break;
		case 'q'://quit
			cout<<"Thank you for using polyCalc!"<<endl;
			break;
		default://other values that is not one of the above
			cout<<"Invalid Character"<<endl;
	}
	}while(prompt != 'q');
	return 0;
}	




