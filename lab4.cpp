#include<bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;



void printPages(vector<int> a ,int page,string f){
  string s=" ";

    for(int i = 0;!(a.empty());i++ ){
       string temp = to_string(a[i]);
       if(a[i]<10)
            s=s+" 0"+temp;
       else
           s=s+" "+temp;
        a.pop_back();
    }
     if(page<10)
         printf("0%d %s %s ",page,f.c_str(),s.c_str());
    else
        printf("%d %s %s ",page,f.c_str(),s.c_str());
    printf("\n");
    }


void FIFO(int pages[], int n, int capacity)
{   //using set to check the page exist or not
    vector<int>l;
    int pageFaults = 0;
    queue<int> q;
    cout<<"Replacement Policy = FIFOn";
    cout<<"--------------------------------------\n";
    cout<<"Page   Content of Frames\n";
    cout<<"-----   -----------------\n";
    for (int i=0; i<n; i++)
    {
        //check for spaces in list
        if (l.size() < capacity)
        {
            //check that pages not exist in set
            if (find(l.begin(), l.end(), pages[i]) == l.end())
            {
                l.push_back(pages[i]);
                q.push(pages[i]);
                printPages(l,pages[i]," ");

            }else{
                printPages(l,pages[i]," ");
            }


            }
        else
        {   //check that pages not exist in set
            if (find(l.begin(), l.end(), pages[i]) == l.end())
            {
                 int temp = q.front();
                 q.pop();
                 l.erase(l.begin());
                 l.push_back(pages[i]);
                 q.push(pages[i]);
                 pageFaults++;

                 printPages(l,pages[i],"F");
            }
            else{
                printPages(l,pages[i]," ");
            }


        }

    }
    cout<<"-------------------------------------\n";
    cout<<"Number of page faults = "<<pageFaults;
    //cout<<"\n";
}

void LRU(int pages[], int n, int capacity)
{

    vector<int> l;
    map<int, int> indexes;
    int pageFaults = 0;
    int index;
    cout<<"Replacement Policy = LRU\n";
    cout<<"-------------------------------------\n";
    cout<<"Page   Content Of Frames\n";
    cout<<"----   -----------------\n";
    for (int i=0; i<n; i++)
    {
        // Check if the set can hold more pages
        if (l.size() < capacity)
        {
            // Insert it if not present
            if (find(l.begin(), l.end(), pages[i]) == l.end())
            {
                l.push_back(pages[i]);

                printPages(l,pages[i]," ");

            }else{

                printPages(l,pages[i]," ");

            }
        //Store the recently used index of  each page
         indexes[pages[i]] = i;
        }

        else
        {   // Insert it if not present
            if (find(l.begin(), l.end(), pages[i]) == l.end())
            {
                // Find the least recently used pages
                int lru = INT_MAX, val;
                for (auto it=l.begin(); it!=l.end(); ++it)
                {
                    if (indexes[*it] < lru)
                    {
                        lru = indexes[*it];
                        val = *it;
                        index=distance(l.begin(), it);

                    }
                }


                l.erase(l.begin()+index);
                // insert the current page
                l.insert(l.begin()+index,pages[i]);
                // Increment page faults
                pageFaults++;

               printPages(l,pages[i],"F");

            }
            else{

             printPages(l,pages[i]," ");

            }
            indexes[pages[i]] = i;
        }

    }
    cout<<"-------------------------------------\n";
    cout<<"Number Of Page Faults = "<<pageFaults;
    cout<<"\n";
}

bool search(int key, vector<int>& fr)
{
    for (int i = 0; i < fr.size(); i++)
        if (fr[i] == key)
            return true;
    return false;
}

//find frame that will not be used in future
int farthestUsed(int pg[], vector<int>& fr, int pn, int index)
{
    // Store the index of pages which are going to be used recently in future
    int res = -1;
    int farthest = index;
    for (int i = 0; i < fr.size(); i++) {
        int j;
        for (j = index; j < pn; j++) {
            if (fr[i] == pg[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        // return  page if  never referenced in future,
        if (j == pn)
            return i;
    }
   //if all the frame not in future return 0
    if(res==-1){
        return 0;
    }else{

        return res;
    }

}

void optimalPage(int pages[], int n, int capacity)
{
    int pageFaults=0;
    vector<int>l;
    cout<<"Replacement Policy = OPTIMAL\n";
    cout<<"-------------------------------------\n";
    cout<<"Page   Content Of Frames\n";
    cout<<"----   -----------------\n";
    for (int i = 0; i < n; i++) {
        // Page found in a frame
        if (search(pages[i], l)) {
            printPages(l,pages[i]," ");
            continue;
        }

        // Page not found in a frame
        // If there is space available in frames.
        if (l.size() < capacity){
            l.push_back(pages[i]);
            printPages(l,pages[i]," ");
        }
        // Find the page to be replaced.
        else {
            int j = farthestUsed(pages, l, n, i + 1);
            l[j] = pages[i];
            pageFaults++;
            printPages(l,pages[i],"F");

        }
    }
      cout<<"-------------------------------------\n";
      cout<<"Number Of Page Faults = "<<pageFaults;
      cout<<"\n";

}


void clock(int pages[],int n,int capacity){
  cout<<"Replacement Policy = CLOCK\n";
  cout<<"-------------------------------------\n";
  cout<<"Page   Content Of Frames\n";
  cout<<"----   -----------------\n";
	int i,j,p=0,pagefault=0,flag=0,use_bit[3],fault=0,k;
	int buffer[3];
	vector<int>b;
	for(i=0;i<capacity;i++){//initialize buffer and use bit
		buffer[i]=-1;
		use_bit[i]=0;
	}
       for(i=0;i<n;i++){//loop for the pages
		for(j=0;j<3;j++){//check if page already exists in the buffer
			if(buffer[j]==pages[i]){
				flag=1;
				use_bit[j]=1;//set use bit
			}
		}
		if(flag==0){//if it doesn't exists then...
			while(flag!=1){
				//check if the buffer has an empty place
				if(use_bit[p]==0&&buffer[p]==-1){
					buffer[p]=pages[i];
					b.push_back(pages[i]);
					use_bit[p]=1;
					flag=1;
				}
				else if(use_bit[p]==0&&buffer[p]!=-1){//if not
					buffer[p]=pages[i];
					b.erase(b.begin()+p);
					b.insert(b.begin()+p,pages[i]);
					use_bit[p]=1;
					flag=1;
					pagefault++;
					fault=1;
					}
				//then buffer is full so we set the use bit to 0 to remove that page from buffer the next time
				else
					use_bit[p]=0;
				p=(p+1)%3;
			}

		}
	if(fault==1)
		printPages(b,pages[i],"F");
	else
		printPages(b,pages[i]," ");

	flag=fault=0;//reset

}
	printf("-------------------------------------\n");
	printf("Number of page faults = %d\n",pagefault);
  cout<<"\n";
}





int main()
{
    //char file[256]="FIFO";
    int n=0;
    int frames;
    int temp;
    char algo[100];
    int refrence[100];
    cin>>frames;
    cin>>algo;

    while (temp!=-1){
        cin>>temp;
        refrence[n]=temp;
          n++;



    }



    if (strcmp(algo,"FIFO")==0)
    {
     FIFO(refrence,n,frames);
    }
    if (strcmp(algo,"LRU")==0)
    {
     LRU(refrence,n,frames);
    }
    if (strcmp(algo,"OPTIMAL")==0)
    {
     optimalPage(refrence,n,frames);
    }
    if (strcmp(algo,"CLOCK")==0)
    {
     clock(refrence,n,frames);
    }





    return 0;
}
