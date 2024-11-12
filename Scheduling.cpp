#include<iostream>
#include<climits>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

class process{
public:
    int id,at,bt,ct,wt,tat,p;
    process(int id_inp , int arrival , int burst ,int priority)
    {
        id = id_inp;
        at = arrival;
        bt = burst;
        p = priority;
        wt= 0;
        ct = 0 ;
        tat =0;

    }
};

bool cmp_at( process a ,process b)
{
    return a.at < b.at;
}

bool cmp_p(process a, process b)
{
    return a.p < b.p;
}

class scheduling_algo{
    int n=0 ;

    float avg_wt(vector<process> proc)
    {
        float awt = 0.0;
        for (int i  =0 ; i<n ; i++)
        {
            awt += proc[i].wt;
        }
        return awt/n;
    }

    float avg_tat(vector<process> proc)
    {
        float atat = 0.0;
        for (int i  =0 ; i<n ; i++)
        {
            atat += proc[i].tat;
        }
        return atat/n;
    }

    void display ( vector<process> proc , string algo)
    {
        cout<<"Gantt Chart for "<<algo<<" Scheduling algo"<<endl;
        cout<<"ID"<<"\tArrival Time"<<"\tBurst Time"<<"\tCompletion Time"<<"\tTurn Around Time"<<"\tWaiting Time"<<"\tPriority"<<endl;
        for (size_t i = 0; i < n; i++)
        {
           cout<<proc[i].id<<"\t\t"<<proc[i].at<<"\t\t"<<proc[i].bt<<"\t\t"<<proc[i].ct<<"\t\t"<<proc[i].tat<<"\t\t"<<proc[i].wt<<"\t\t"<<proc[i].p<<"\t\t"<<endl;
        }
        
        cout<<"Average Waiting Time: "<<avg_wt(proc)<<endl;
        cout<<"Average Turn Around Time: "<<avg_tat(proc)<<endl;
    }

public:
    scheduling_algo(int size){ n=size;}

    void FCFS(vector<process> proc)
    {
        sort(proc.begin() , proc.end(), cmp_at);

        proc[0].ct = proc[0].bt + proc[0].at;
        proc[0].tat = proc[0].ct - proc[0].at;
        proc[0].wt  = proc[0].tat - proc[0].bt;

        for(int i=1 ; i< n ; i++)
        {
            proc[i].ct = max(proc[i-1].ct , proc[i].at) +proc[i].bt;
            proc[i].tat = proc[i].ct - proc[i].at;
            proc[i].wt  = proc[i].tat - proc[i].bt;
        }

        display(proc ,"FCFS");
    }

    void Priority(vector<process> proc)
    {
        sort(proc.begin(), proc.end(), cmp_p);

        proc[0].ct = proc[0].bt + proc[0].at;
        proc[0].tat = proc[0].ct - proc[0].at;
        proc[0].wt  = proc[0].tat - proc[0].bt;

        for(int i=1 ; i< n ; i++)
        {
            proc[i].ct = max(proc[i-1].ct , proc[i].at) +proc[i].bt;
            proc[i].tat = proc[i].ct - proc[i].at;
            proc[i].wt  = proc[i].tat - proc[i].bt;
        }

        display(proc ,"Priority");
    }

    void RoundRobin(vector<process> proc)
    {
        int currtime = 0 ;
        queue<int> rq;
        vector<bool> inQueue(n,false);
        int rt[n];
        int tq;

        cout<<"Enter Time Quantum: ";
        cin>>tq;

        for (int i = 0; i < n; i++)
           rt[i]= proc[i].bt;

        for(int j = 0 ; j < n ; j++)
        {
            if(proc[j].at <= currtime) //<= condition not < only!!
            {
                rq.push(j);
                inQueue[j] = true;
            }
        }

        while (!rq.empty())
        {
            int cur = rq.front();
            rq.pop();

            if (rt[cur]>tq)
            {
                currtime += tq;
                rt[cur] -= tq;
            }

            else
            {
                currtime += rt[cur];
                rt[cur] = 0;

                proc[cur].ct  = currtime;
                proc[cur].tat = proc[cur].ct - proc[cur].at;
                proc[cur].wt  = proc[cur].tat - proc[cur].bt;
            }
            
            for(int x = 0 ; x<n ; x++)
            {
                if(inQueue[x]==false && proc[x].at <= currtime)
                {
                    rq.push(x);
                    inQueue[x]=true; //this was missing 
                }
            }

            if(rt[cur] > 0)
                rq.push(cur);

        }
        
        display(proc,"Round Robin");
    }

    void SJF(vector<process> proc)
    {
        int  currtime = 0 ,shortest = 0; //also define value of shortst!!
        int mintime = INT_MAX; //you have to define what is value in order to compare
        int rt[n];
        int complete = 0;
        bool found = false;

        for (int i = 0; i < n; i++)
            rt[i]= proc[i].bt;
        
        while(complete < n)
        {
            for (int j = 0; j < n ; j++)
            {
                // if( proc[j].at <= currtime &&  rt[j] < mintime)
                if(proc[j].at <= currtime && rt[j] < mintime && rt[j] > 0)
                {
                    shortest = j ; 
                    mintime = rt[j];
                    found = true;
                }
            }
            rt[shortest]--;
            mintime = rt[shortest];

            if(rt[shortest] == 0)
            {
                mintime = INT_MAX ;//reinitialize the value!!!
                complete ++;
                found = true;
                proc[shortest].ct = currtime+1; //+1 required!!
                proc[shortest].tat = proc[shortest].ct - proc[shortest].at;
                proc[shortest].wt = proc[shortest].tat - proc[shortest].bt;
            }

            currtime++;   
        }
        display(proc,"SJF");
    }

};

int main()
{
     int size;
    cout<<"Enter number of processes :";
    cin>>size;

    vector<process> processses;
    cout<<"For each process enter: ";
    for (int i = 0; i < size; i++)
    {
        int a , b , p;
        cout<<"Arrival time: ";
        cin>>a;
        cout<<"Burst time: ";
        cin>>b;
        cout<<"Priority";
        cin>>p;

        process obj(i+1, a, b,p);
        processses.push_back(obj);
    }

    //     int size;
//     cout<<"Enter Number of Processes: ";
//     cin>>size;
//    // Scheduling_algo obj(size);
//     process proc_list[size];
//     for(int a = 0; a<size;a++)
//     {
//         process proc;
//         cout<<"Enter Process id: ";
//         cin>>proc.id;
//         cout<<"Enter Process Arrival time: ";
//         cin>>proc.at;
//         cout<<"Enter Process Burst time: ";
//         cin>>proc.bt;
//         cout<<"Enter Priority: ";
//         cin>>proc.p;
//         proc_list[a]=proc;
//     }




    scheduling_algo sa(size);

    sa.FCFS(processses);
    sa.Priority(processses);
    sa.RoundRobin(processses);
    sa.SJF(processses);


    return 0;

}
