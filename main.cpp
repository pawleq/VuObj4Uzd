#include "funkcijos.cpp"
int main ()
{
	multimap<string, int> WordCounter;
	vector<string> links;
	string pav;
    readANDfind(WordCounter, links, pav);
    printOutWordsAndLinks(WordCounter, links, pav);
}
