#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <string>
#include <stack>

using namespace std;

void printArray(int arr[], int len)
{
    int i = 0;
    for( i=0; i< len; i++ )
    {

        printf("%02d ",arr[i]);

    }
    printf("\n");
    return;
}

void lru(vector<int> page_sequence, int allocated_page_size){


printf("Replacement Policy = LRU\n");
printf("-------------------------------------\n");
printf("Page   Content of Frames\n");
printf("----   -----------------\n");
    int page_faults = 0;

    int frames[allocated_page_size];

    int frames_len = page_sequence.size(),i,current_size = 0;

    set<int> current;
    set<int> current_helper;

    vector<int> s;

    for(i=0; i< frames_len; i++)
    {
        
        if( current_size < allocated_page_size)
        {
            if( current.find( page_sequence.at(i)) == current.end() )
            {
                frames[current_size++] = page_sequence.at(i);
                current.insert(page_sequence.at(i) );
            }
            s.push_back( page_sequence.at(i));
            printf("%02d     ", page_sequence.at(i));
            printArray(frames, current_size);
            continue;
        }else
        {
        
            if( current.find( page_sequence.at(i)) != current.end() )
            {
                s.push_back( page_sequence.at(i) );
                printf("%02d     ", page_sequence.at(i));
                printArray(frames, current_size);
                continue;
            }
            current_helper.clear();
            current_helper.insert( current.begin(), current.end());
            int j= s.size()-1;
            while( current_helper.size() > 1 && j >= 0)
            {
                if( current_helper.find(s.at(j) ) != current_helper.end() )
                    current_helper.erase(current_helper.find( s.at(j)));
                j--;
            }
            int temp;
            if( !current_helper.empty())
               temp = *current_helper.begin();

            for(j=0; j< allocated_page_size; j++)
            {
                if( frames[j] == temp )
                {
                    break;
                }
            }
            frames[j] = page_sequence.at(i);
            s.push_back( page_sequence.at(i) );
            current.insert(page_sequence.at(i) );
            current.erase( current.find( temp));
            printf("%02d ", page_sequence.at(i));
            printf("F   ");
            printArray(frames, current_size);
            page_faults++;
            
        }
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", page_faults);
    return;
}

void fifo(vector<int> page_sequence, int allocated_page_size){

    printf("Replacement Policy = FIFO\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");
    int page_faults = 0;

    int frames[allocated_page_size];

    int next_to_remove = 0, frames_len = page_sequence.size(),i,current_size = 0;

    set<int> current;

    for(i=0; i< frames_len; i++)
    {
        if( current_size < allocated_page_size)
        {
            if( current.find( page_sequence.at(i)) == current.end() )
            {
                frames[current_size++] = page_sequence.at(i);
                current.insert(page_sequence.at(i) );
            }

            printf("%02d     ", page_sequence.at(i));
            printArray(frames, current_size);
            continue;
        }else
        {
            if( current.find( page_sequence.at(i)) != current.end() )
            {
                printf("%02d     ", page_sequence.at(i));
                printArray(frames, current_size);
                continue;
            }

            current.erase( current.find(frames[ next_to_remove]) );
            frames[ next_to_remove] = page_sequence.at(i);
            current.insert(page_sequence.at(i) );
            next_to_remove = (next_to_remove+1)%allocated_page_size;
            printf("%02d ", page_sequence.at(i));
            printf("F   ");
            printArray(frames, current_size);
            page_faults++;
        }
    }
printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", page_faults);
    return;
}
void optimal(vector<int> page_sequence, int allocated_page_size ){

 int frames[allocated_page_size];


printf("Replacement Policy = OPTIMAL\n");
printf("-------------------------------------\n");
printf("Page   Content of Frames\n");
printf("----   -----------------\n");
    set<int> current;


    int frames_len = page_sequence.size();
    int i=0,j=0;



    int page_faults = 0;
    int current_size = 0;
    int replacement_index;
    int value;

    for(i=0; i<frames_len; i++)
    {

        if( current_size < allocated_page_size )
        {
            if( current.find( page_sequence.at(i)) == current.end())
            {
              frames[ current_size++ ] = page_sequence.at(i);
              current.insert( page_sequence.at(i) );
            }

            printf("%02d     ", page_sequence.at(i));
            printArray(frames, current_size);
            continue;
        }

        else
        {

        if( current.find(page_sequence.at(i) ) != current.end() )
        {
            printf("%02d     ", page_sequence.at(i));
            printArray(frames, current_size);
            continue;
        }
        printf("%02d ", page_sequence.at(i));
        printf("F   ");
        page_faults++;

        value = -1;
        replacement_index = 0;
        int k = 0;

        for(k=0; k< allocated_page_size; k++)
        {
            for( j = i+1; j< frames_len; j++)
            {
                if( frames[k] == page_sequence.at(j) )
                {
                  if(  j > value )
                  {
                        value = j;
                        replacement_index = k;
                  }
                  break;
                }
            }
            if( j == frames_len)
            {
                value = 0;
                replacement_index = k;
                break;
            }
        }

        current.erase( frames[replacement_index] );
        current.insert(page_sequence.at(i) );
        frames[replacement_index] = page_sequence.at(i);


            printArray( frames, current_size);

        }
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", page_faults);
}

void clock(vector<int> page_sequence, int allocated_page_size)
{

    printf("Replacement Policy = CLOCK\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    int frames[allocated_page_size];
    int frames_len = page_sequence.size(), i=0,j=0, current_size=0;
    bool stared[allocated_page_size];
    int pointer = 0, page_faults=0;

    for(i=0; i< allocated_page_size; i++)
    {
	stared[i] = false;
    }

    for(i=0; i< frames_len; i++)
    {
        if( current_size < allocated_page_size)
        {
            for(j=0; j< current_size; j++)
            {
                if( frames[j] == page_sequence.at(i) )
                {
			     stared[j] = true;
			     break;
                }
            }
		if( j == current_size)
		{
		   frames[current_size++] = page_sequence.at(i);
		   pointer = ( pointer + 1)% allocated_page_size;
		   stared[current_size-1] = true;
		}

                printf("%02d     ", page_sequence.at(i));
                printArray(frames, current_size);
                continue;
        }else

	{
                

		for(j=0; j<allocated_page_size; j++)
		{
		    if( frames[j] == page_sequence.at(i) )
		     {
                            printf("%02d     ", page_sequence.at(i));
			    stared[j] = true;
			    break;
		     }
		}
		if( j == allocated_page_size)
		{
                     printf("%02d ", page_sequence.at(i));
                     printf("F   ");
		     page_faults++;
		     while( true)
			{
				if( !stared[pointer] )
				{
				     frames[pointer] = page_sequence.at(i);
				     stared[pointer] = true;
				     pointer = ( pointer + 1)%allocated_page_size;
				     break;
				}else
				{
				    stared[pointer] = false;
				    pointer = ( pointer + 1)%allocated_page_size;
				}
			}
		}

            printArray(frames, current_size);
        }
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", page_faults);
return;
}

int main()
{
    int allocated_page_size;
    string choice;
    scanf("%d", &allocated_page_size);
    cin>>choice;
    vector<int> page_sequence;
    int temp;

    scanf("%d", &temp);

    while( temp != -1)
    {
        page_sequence.push_back( temp);
        scanf("%d", &temp);
    }




    if( choice == "OPTIMAL")
        optimal(page_sequence, allocated_page_size);
    else if( choice == "FIFO")
        fifo(page_sequence, allocated_page_size);
    else if( choice == "LRU")
        lru(page_sequence, allocated_page_size);
        else if( choice == "CLOCK")
        clock(page_sequence, allocated_page_size);
else 
printf("invalid input");

    return 0;
}
