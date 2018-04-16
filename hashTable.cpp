#include <iostream>
#include <fstream>
#include <string>


using namespace std;


class WordEntry
{
      private:
            int value;
            string word_read_in;
                  
      public:
      
           WordEntry( int value, string word_read_in )
           {
                 this->value = value;
                 this->word_read_in = word_read_in;
           }
           
           string getKey()
           {
                 return word_read_in;
           }
           
           int getValue()
           {
                 return value;
           }
           
           void setValue( int value )
           {
                 this->value = value;
           }
};

const int TABLE_SIZE = 100;

class HashMAP
{
      private:
            WordEntry ** table;
            
      public:
            HashMAP()
            {
                  table = new WordEntry*[TABLE_SIZE];
                  for( int i=0; i<TABLE_SIZE; i++ )
                  {
                        table[i] = NULL;
                  }
            }
            
            void put( int value, string word_read_in )
            {
                  int hash = ( word_read_in.length() % TABLE_SIZE );
                  
                  while( table[hash] != NULL && table[hash]->getKey() != word_read_in )
                        hash = ( hash + 1 ) % TABLE_SIZE;
                        
                  if( table[hash] != NULL )
                        delete table[hash];
                        
                  table[hash] = new WordEntry(value, word_read_in);
            }
     
            
            string dictateCase( string raw_word )
            {
                  for( int i = 0; i<raw_word.length(); i++ )
                        raw_word[i] = toupper(raw_word[i]);
            
                  return raw_word;
            }
            
            
            void showContents()
            {
                  int general_count = 0;
                  
                  for ( int i = 0; i<TABLE_SIZE; i++)
                        if( table[i] != NULL )
                              general_count++;
                  
                  general_count;            
                  cout<<"There is/are "<<general_count <<" distinct word(s) in the file's text."<<endl;
            }
  
            int Search( string word_read_in )
            {
                  string word = word_read_in;
                  
                  word = dictateCase(word);
                  
                  int hash = ( word.length() % TABLE_SIZE );
                   
                  while( table[hash] != NULL && table[hash]->getKey() != word )
                        hash = ( hash + 1 ) % TABLE_SIZE;
                        
                  if( table[hash] == NULL )
                        return 0;
                  else
                        return table[hash]->getValue();
            }
            
            
            ~HashMAP()
            {
                  for( int i = 0; i< TABLE_SIZE; i++ )
                        if( table[i] != NULL )
                              delete table[i];
                              
                  delete[] table;
            }
};


string dictateCase( string raw_word )
{
      for( int i = 0; i<raw_word.length(); i++ )
            raw_word[i] = toupper(raw_word[i]);
            
      return raw_word;
}


int main ()
{
      HashMAP instantaneous;
  
      int count, value ;
      
      string word, caseCorrectedWord;
 
      ifstream myFile;
      myFile.open("sampleWords.txt");
      
      if( !myFile.is_open() )
            cout<<"Ooops, couldn't open file mentioned sorry buddy."<<endl;
            
      else
      {
            while( !myFile.eof() )
            {
                  myFile >> word;
                                   
                  caseCorrectedWord = dictateCase(word);
                  int count = instantaneous.Search(caseCorrectedWord);
                  count++;
                  instantaneous.put(count, caseCorrectedWord);
            }
      }
      
      instantaneous.showContents();
      
      //value = instantaneous.Search("possible");
      
      //cout<<"Value found is "<< value <<endl;
      
      return 0;
}