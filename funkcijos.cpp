#include "main.h"
bool Url(const string &word)
{
    regex rgx("(http[s]?:\\/\\/(www\\.)?|ftp:\\/\\/(www\\.)?|www\\.){1}([0-9A-Za-z-\\.@:%_\+~#=]+)+((\\.[a-zA-Z]{2,3})+)(/(.)*)?(\\?(.)*)?");//regex bilbioteka leidzia aptikti tam tikrus simbolius zodyje
    return regex_match(word, rgx);
}
bool specialchar(char & a)
{
    if (isalpha(a) or isdigit(a))
    {
        return false;
    }
    return true;
}
void readANDfind (multimap<string, int> & WordCounter, vector<string> & links, string & pav)
{
    cout << "Iveskite studentu failo pavadinima" << endl;
    cin >> pav;
    ifstream in(pav);
    if (!in)
    {
        cout << "Pavadinimas ivestas neteisingai" << endl;
        exit(EXIT_FAILURE);
    }
    int linenr = 1;
    while (!in.eof())
    {
        string line;
        getline(in, line);
        stringstream eil(line);
        string word;
        while (eil >> word)
        {
            transform(word.begin(), word.end(), word.begin(), ::tolower);//zodziuose dingsta mazosios raides
            if (Url(word))//jeigu zodis yra linkas, jis idedamas i links vektoriu
            {
                links.push_back(word);
            }
            else
            {
                word.erase(remove_if(word.begin(), word.end(), specialchar), word.end());//panaikinami simboliai is zodzio
                if (!word.empty())
                    WordCounter.insert({ word, linenr });//idedamas zodis be simboliu i konteineri
            }
        }
        linenr++;
    }
    in.close();
}
void printOutWordsAndLinks (multimap<string, int> & WordCounter, vector<string> & links, string & pav)
{
    ofstream out("words&linksFrq.txt");
    out<<setw(20)<<left<<"Zodis"<<setw(21)<<"pakartojimu skaicius"<<" "<<"eilutese"<<endl;
    for (auto it = WordCounter.begin(), end = WordCounter.end(); it != end; it = WordCounter.upper_bound(it->first)) //"it = WordCounter.upper_bound(it->first)" leidzia spausdinti tik nepasikartojancius zodzius
    {
        if (WordCounter.count(it->first) > 1)//tiktrinama, kurie zodziai kartojosi bent daugiau nei 1 karta
        {
            out<<setw(20)<<left<< it->first <<setw(21)<<left<<WordCounter.count(it->first);
            for (auto itline = WordCounter.equal_range(it->first).first; itline != WordCounter.equal_range(it->first).second; ++itline)//kiekvienam zodziui, kuris pasikartojo n kartu, yra vykdomas ciklas tiek kartu, kiek tas zodis kartu kartojosi
            {
                out <<" "<<itline->second; //isvademos eilutes, kur kartojosi zodis
            }
            out << endl;
        }
    }
    out << "Links: " << endl;
    for (auto it = links.begin(); it != links.end(); it++)
    {
        out << *(it) << endl;
    }
}
