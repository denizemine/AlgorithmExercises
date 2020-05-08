//***************************
//*******152120161025********
//*******Emine DENÝZ*********
//***************************

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Midterm.h"
#include <map>
#include<unordered_map>
#include <queue>
using namespace std;

///============================ PolynomialAddition ====================

PolyNode* PolynomialAddition(PolyNode* P1, PolyNode* P2) {

	PolyNode* result = (PolyNode *)malloc(sizeof(PolyNode));
	PolyNode *result2 = (PolyNode *)malloc(sizeof(PolyNode));
	result2 = result;

	if (P1 == NULL && P2 == NULL) return NULL;
	else if (P1 != NULL && P2 == NULL) return P1;
	else if (P1 == NULL && P2 != NULL) return P2;
	while (P1 && P2)
	{
		if (P1->exp > P2->exp)
		{
			result->exp = P2->exp;
			result->coeff = P2->coeff;
			P2 = P2->next;
		}//end-if
		else if (P1->exp < P2->exp)
		{
			result->exp = P1->exp;
			result->coeff = P1->coeff;
			P1 = P1->next;
		}//end-else if
		else
		{
			//-3x^2 + 3x^2
			if (P1->coeff == -(P2->coeff))
			{
				P1 = P1->next;
				P2 = P2->next;
			}//end-if
			result->exp = P2->exp;
			result->coeff = P1->coeff + P2->coeff;
			P1 = P1->next;
			P2 = P2->next;
		}//end-else
		if (P1 && P2)
		{
			result->next = (PolyNode *)malloc(sizeof(PolyNode));
			result = result->next;
			result->next = NULL;
		}//end-if

	}//end-while
	while (P1) {

		if (P1->next) {
			result->exp = P1->exp;
			result->coeff = P1->coeff;
			P1 = P1->next;
		}//end-if
		result->next = (PolyNode*)malloc(sizeof(PolyNode));
		result = result->next;
	}//end-while
	while (P2) {

		if (P2->next) {
			result->exp = P2->exp;
			result->coeff = P2->coeff;
			P2 = P2->next;
		}//end-if
		result->next = (PolyNode*)malloc(sizeof(PolyNode));
		result = result->next;
	}//end-while
	result->next = NULL;
	return result2;
} //end-PolynomialAddition

///============================ TwoDimensionalWordSearch ====================
bool WordSearchRecursive(vector<string>& matrix, string& p, int row, int col, int word_index, vector<Index>& Indicies)
{
	//boundry
	if (row < 0 || row >= matrix.size()) return false;
	if (col < 0 || col >= matrix[0].size()) return false;
	if (matrix[row][col] == '*' || p[word_index] != matrix[row][col]) return false;
	Index index = Index(row, col);
	//eðer word'ün son degeride bulunduysa true dön
	if (word_index == p.size() - 1) {
		Indicies.push_back(index);
		return true;
	}//end-if
	//bulunan harfleri *  yapmak için board'u bir tempe atýp iþlem bittikten sonra wordün eski deðerini almasý için :
	char temp = matrix[row][col];
	matrix[row][col] = '*';
	Indicies.push_back(index);

	if (WordSearchRecursive(matrix, p, row + 1, col, word_index + 1, Indicies)) return true;//down
	if (WordSearchRecursive(matrix, p, row, col + 1, word_index + 1, Indicies)) return true;//right
	if (WordSearchRecursive(matrix, p, row - 1, col, word_index + 1, Indicies)) return true;//up
	if (WordSearchRecursive(matrix, p, row, col - 1, word_index + 1, Indicies)) return true;//left

	matrix[row][col] = temp;
	return false;
}//end-WordSearchRecursive
bool TwoDimensionalWordSearch(vector<string>& A, string& pattern, vector<Index>& patternIndicies) {
	if (A.size() == NULL || pattern.size() == NULL) return false;

	//A vektöründe patternin ilk elemanýný bulup search fonksiyonuna row,col,pattern 0'ý gönderilir.
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[0].size(); j++) {
			if (A[i][j] != pattern[0]) continue;
			patternIndicies.clear();
			if (WordSearchRecursive(A, pattern, i, j, 0, patternIndicies)) {
				return true;
			}


		}//end-for
	}//end-for
	return false;
} //end-TwoDimensionalWordSearch


///============================ IntervalSum ====================
void IntervalSum(vector<int>& A, vector<int> &Sum) {

	if (A.size() == 0) Sum.empty();
	int tmp = 0, count = 0;
	unordered_map<int, int> map;
	Sum.assign(A.size(), 0);

	for (auto vectorIter = A.begin(); vectorIter != A.end(); vectorIter++) {

		auto mapIter = map.find(*vectorIter);
		tmp += *vectorIter;

		if (mapIter != map.cend()) {
			Sum[count] = (int)(tmp - *vectorIter - mapIter->second);
			mapIter->second = tmp;
		}
		else {
			map.insert({ (int)*vectorIter, tmp });
		}

		count++;
	}
} //end-IntervalSum

///=========================== MergeKSortedSeqs ================================
/// Takes in "k" sorted sequences of "n" total integers, and merges them all into a 
/// single sorted sequence in O(nlogk) time
///
// int:iteratörün içindeki deðer ,  vector<Sequence>::iterator:iteratörün kendisi

struct ppi {
	int first;
	vector<Sequence>::iterator second;
	ppi(int no, vector<Sequence>::iterator f) { first = no; second = f; }
};
void MergeKSortedSeqs(vector<Sequence>& seqs, vector<int>& sortedArray) {
	if (seqs.size() == 0) sortedArray.empty();
	auto &cmp = *&[](ppi& first, ppi& second) {return (first.first > second.first); };
	priority_queue<ppi, vector<ppi>, decltype(cmp) > Q(cmp);

	for (vector<Sequence>::iterator i = seqs.begin(); i != seqs.end(); i++)
		Q.push({ (int)*((*i).start), i });//typedef pairi içeriyor. (int)((*i).start):value i

	while (Q.size() > 0) {
		ppi top = Q.top();
		Q.pop();
		vector<Sequence>::iterator v = top.second;
		sortedArray.push_back(top.first);

		if ((*v).start + 1 != (*v).end) {
			(*v).start = (*v).start + 1;
			Q.push({ (int)*(*v).start, v });
		}//end-if
	}//end-while	
} //end-MergeKSortedSeqs