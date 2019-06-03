#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

class _minterm {
public:
   int dec;
   int bin;
   int numof1;
   bool combined;
   vector<int> decs;
   bool epi;

   bool operator<(const _minterm& m) const {
      return (numof1 < m.numof1);
   }
};

// make binary look like decimal
int dec_to_bin(int a)
{
   int res = 0;
   for (int i = 1; a > 0; i *= 10)
   {
      int bin = a % 2;
      res += bin * i;
      a /= 2;
   }

   return res;
}

int count_number_of_1s(int a)
{
   int cnt = 0;
   while (a != 0)
   {
      if (a % 10 == 1) cnt++;
      a /= 10;
   }
   return cnt;
}

bool compare(int n, int a, int b)
{
   int hamming = 0;
   while (n != 0)
   {
      if ((a % 10) != (b % 10)) hamming++;
      a /= 10;
      b /= 10;
      n--;
   }
   if (hamming == 1) return true;
   else return false;
}

int combine(int a, int b)
{
   int tmp, res;
   if (a > b)
   {
      tmp = a - b;
      res = a + tmp;
   }
   else
   {
      tmp = b - a;
      res = b + tmp;
   }
   return res;
}

vector<string> solution(vector<int> input) {
   vector<string> answer;
   int n = input[0];
   int m = input[1];
   bool nothing_combined = false;
   vector<_minterm> pi;
   vector<int> epi;
   vector<int> nepi;
   vector<vector<vector<_minterm> > > number;
   vector<vector<_minterm*> > cover;
   vector<vector<_minterm> > tmp;
   vector<_minterm> tmp2;
   vector<_minterm*> tmp3;

   int level = 0;

   for (int i = 0; i < pow(2, n); i++)
   {
      tmp.push_back(tmp2);
      cover.push_back(tmp3);
   }
   number.push_back(tmp);

   // minterm initialize
   for (int i = 0; i < m; i++)
   {
       struct _minterm minterm;
      minterm.dec = input[i + 2];
      minterm.decs.push_back(minterm.dec);
      minterm.bin = dec_to_bin(minterm.dec);
      minterm.numof1 = count_number_of_1s(minterm.bin);
      minterm.decs.push_back(minterm.dec);
      number[0][minterm.numof1].push_back(minterm);
   }
   sort(number.begin(), number.end());
   number.push_back(tmp);

   //combine
   while (!nothing_combined)
   {
      number.push_back(tmp);
      for (int i = 0; i < number[level].size() - 1; i++)
      {
         for (int j = 0; j < number[level][i].size(); j++)
         {
            for (int k = 0; k < number[level][i + 1].size(); k++)
            {
               if (compare(n, number[level][i][j].bin, number[level][i + 1][k].bin))
               {
                   struct _minterm minterm;
                   minterm.bin = combine(number[level][i][j].bin, number[level][i + 1][k].bin);
                   minterm.numof1 = i;
                   for(int ii=0; ii<number[level][i][j].decs.size(); ii++)
                   {
                       minterm.decs.push_back(number[level][i][j].decs[ii]);
                   }
                   for(int ii=0; ii<number[level][i][j].decs.size(); ii++)
                   {
                       minterm.decs.push_back(number[level][i+1][k].decs[ii]);
                   }
                   //printf("push_back %d %d\n", number[level][i][j].dec, number[level][i + 1][k].dec);
                   minterm.decs.erase(unique(minterm.decs.begin(),minterm.decs.end()),minterm.decs.end());

                  minterm.epi = false;
                  minterm.combined = false;

                  number[level][i][j].combined = true;
                  number[level][i + 1][k].combined = true;

                  number[level + 1][i].push_back(minterm);
               }
            }
         }
      }

      // make pi
      nothing_combined = true;
      for (int i = 0; i < number[level].size(); i++)
      {
         for (int j = 0; j < number[level][i].size(); j++)
         {
            if (!number[level][i][j].combined)
            {
               //check duplication
               bool flag = false;
               for (int ii = 0; ii < pi.size(); ii++)
               {
                  if (pi[ii].bin == number[level][i][j].bin) flag = true;
               }
               if (!flag) pi.push_back(number[level][i][j]);
            }
            else nothing_combined = false;
         }
      }
      level++;
   }

   //cover check
   for (int i = 0; i < pi.size(); i++)
   {
      for (int j = 0; j < pi[i].decs.size(); j++)
      {
         int idx = pi[i].decs[j];
         //printf("%d %d %d\n", pi[i].decs.size(), pi[i].bin, pi[i].decs[j]);
         cover[idx].push_back(&(pi.at(i)));
         cover[idx].erase(unique(cover[idx].begin(), cover[idx].end()), cover[idx].end());
      }
   }

   //epi check
   for (int i = 0; i < pow(2, n); i++)
   {
      if (cover[i].size() == 1)
      {
          cover[i][0]->epi = true;
      }
   }

   //push epi, nepi
   for (int i = 0; i < pi.size(); i++)
   {
      if (pi[i].epi) epi.push_back(pi[i].bin);
      else nepi.push_back(pi[i].bin);
   }

   sort(epi.begin(), epi.end());
   sort(nepi.begin(), nepi.end());

   // answer
   answer.push_back("EPI");
   for (int i = 0; i < epi.size(); i++)
   {
      string sbin = "";
      int bin = epi[i];
      for (int j = 0; j < n; j++)
      {
         if (bin % 10 == 0) sbin = "0" + sbin;
         else if (bin % 10 == 1) sbin = "1" + sbin;
         else sbin = "-" + sbin;
         bin /= 10;
      }
      answer.push_back(sbin);
   }
   answer.push_back("NEPI");
   for (int i = 0; i < nepi.size(); i++)
   {
      string sbin = "";
      int bin = nepi[i];
      for (int j = 0; j < n; j++)
      {
         if (bin % 10 == 0) sbin = "0" + sbin;
         else if (bin % 10 == 1) sbin = "1" + sbin;
         else sbin = "-" + sbin;
         bin /= 10;
      }
      answer.push_back(sbin);
   }

   return answer;
}
