#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>

using namespace std;

class mgmt{
public:

    void display(string a , vector<int> proc , vector<int> block , vector<int> alloc)
    {
        cout<<"Memory block allocation for "<<a<<endl;
        cout<<"Available blocks: {";
        for(int j = 0 ; j< block.size() ; j++)
            cout<<" "<<block[j];
        cout<<" }"<<endl;

        cout<<"Proc no"<<"\tProc size"<<"\tBlock number alloted"<<endl;

        for (int i = 0; i < proc.size(); i++)
        {
            cout<<i+1<<"\t"<<proc[i]<<"\t\t"<<alloc[i]<<endl;
        }    
    }

    void first_fit(vector<int> proc , vector<int> block)
    {
        vector<int> alloc(proc.size(),-1);
        vector<bool>isallocated(block.size(),false);

        for (int i = 0; i < proc.size(); i++)
        {
            for (int j= 0; j < block.size(); j++)
            {
                if(block[j] >= proc[i]&& !isallocated[j])
                {
                    isallocated[j]=true;
                    alloc[i]=j+1;
                    break;
                }
            }
            
        }
        display("First Fit",proc,block,alloc);
        
    }

    
    void next_fit(vector<int> proc , vector<int> block)
    {
        vector<int> alloc(proc.size(),-1);
        vector<bool>isallocated(block.size(),false);

        int pointer = 0;
        for (int i = 0; i < proc.size(); i++)
        {
            for (int j= pointer; j < block.size(); j++)
            {
                if(block[j] >= proc[i]&& !isallocated[j])
                {
                    pointer=j;
                    isallocated[j]=true;
                    alloc[i]=j+1;
                    break;
                }
            }
            
        }
        display("Next Fit",proc,block,alloc);
    }

    
    void best_fit(vector<int> proc , vector<int> block)
    {
        vector<int> alloc(proc.size(),-1);
        vector<bool>isallocated(block.size(),false);

        int best;
        for (int i = 0; i < proc.size(); i++)
        {
            best=-1;

            for (int j= 0; j < block.size(); j++)
            {
                if(block[j] >= proc[i]&& !isallocated[j])
                {
                    if(block[best] > block[j] || best ==-1)
                         best = j;
                }
            }

            if(best != -1)
           { alloc[i]=best+1;
            isallocated[best] = true;}
        }
        display("Best Fit",proc,block,alloc);
        
    }

    void wrost_fit(vector<int> proc , vector<int> block)
    {
        vector<int> alloc(proc.size(),-1);
        vector<bool>isallocated(block.size(),false);

        int wrost;
        for (int i = 0; i < proc.size(); i++)
        {
            wrost=-1;

            for (int j= 0; j < block.size(); j++)
            {
                if(block[j] >= proc[i]&& !isallocated[j] )
                {
                    if(block[wrost] < block[j] ||wrost  == -1)
                        wrost = j;
                }
            }

            if(wrost != -1)
            {alloc[i]=wrost+1;
            isallocated[wrost] = true;}
        }
        display("Wrost Fit",proc,block,alloc);
        
    }


};


int main()
{
    // vector<int> proc;
    // vector<int> blocks;

    // int n , m ;
    // cout<<"Enter total processes: ";
    // cin>>n;
    // cout<<"Enter total free blocks:";
    // cin>>m;

    // cout<<"For "<<n<<" process enter proc size"<<endl;
    // for (int i = 0; i < n; i++)
    // {
    //     int a;
    //     cin>>a;
    //     proc.push_back(a);
    // }

    // cout<<"For "<<n<<" empty blocks enter block size"<<endl;
    // for (int i = 0; i < n; i++)
    // {
    //     int b;
    //     cin>>b;
    //     blocks.push_back(b);
    // }


     vector<int> blocks = {12,10,35,15,5,18,6};
    vector<int> proc_size =   {10,20,30,25,15,40};  
    mgmt obj;
    cout<<"goining in wrost fit"<<endl;
    obj.wrost_fit(blocks, proc_size); 
    cout<<endl; 
    cout<<"goining in best fit"<<endl;
    obj.best_fit(blocks, proc_size);
    cout<<endl; 
    cout<<"goining in first fit"<<endl;
    obj.first_fit(blocks, proc_size);
    cout<<endl;
    cout<<"goining in next fit"<<endl;
    obj.next_fit(blocks, proc_size);

    return 0;
    
}