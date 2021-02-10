#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#define RED 'r'
#define BLACK 'b'

using namespace std;
int counter[2000];
vector<string> line;
vector<int>order;
int bNum_search[2000];
int exTime_search[2000];
int totalTime_search[2000];
vector<int> pending_bnum;
vector<int> pending_time;
int search_counter=0;
int capacity=2000;
int global_counter=0;
int heap_size=0;
int goToPrint=-1;
int flag=-1;
int counter_itr=0;
bool goahead=true;
int k=0;
string file_name;
typedef struct node {
    int buildingNum;
    int executed_time;
    int total_time;
    char colour;
    struct node *l, *r, *parent;
}*NODE;

struct node NIL;

NODE NULLPTR = &NIL;
NODE root;
//SEARCHES THE RED BLACK TREE FOR A BUILDING NUMBER
NODE search_RBT(NODE root, int bNum)
{
    if(root==NULLPTR){
        return root;
    }
    else if(root->buildingNum == bNum){
        return root;
    }
    if (bNum >= root->buildingNum){
        return search_RBT(root->r, bNum);
    }
    else{
        return search_RBT(root->l, bNum);
    }
}
//PRINTS RBT IN INORDER SEQUENCE
void print_RBT(NODE n)
{
    if (n != NULLPTR) {
        print_RBT(n->l);
        cout<<n->buildingNum<<" -- ";
        cout<<n->executed_time<<" -- ";
        cout<<n->total_time<<" -- ";
        print_RBT(n->r);
    }
}
//FINDS MINIMUM ELEMENT IN THE RBT
NODE find_minRBT(NODE root)
{
    while (root->l != NULLPTR)
        root = root->l;
    return root;
}
//FINDS MAXIMUM ELEMENT IN THE RBT
NODE find_maxRBT(NODE root)
{
    while (root->r != NULLPTR)
        root = root->r;
    return root;
}
//FINDS BUILDINGS IN RANGE OF 2 SPECIFIED BUILDING NUMBERS, STORES INFORMATION FOR EACH OF THEM IN TEMPORARY ARRAYS
void BuildingsInRange(NODE n,int min,int max,int b1,int b2)
{
    
    if (n == NULLPTR) {
    }
    else{
        //If B1 is less than equal to the min element of heap and b2 is more than equal to max element of the heap(WHOLE TREE PRINTS)
        if(b1<=min &&b2>=max)
        {
            
            BuildingsInRange(n->l,min,max,b1,b2);
            bNum_search[search_counter]=n->buildingNum;
            exTime_search[search_counter]=n->executed_time;
            totalTime_search[search_counter]=n->total_time;
            search_counter++;
            BuildingsInRange(n->r,min,max,b1,b2);
        }
        //If B1 is more than the min element and b2 is at the right most leaf child
        else if(b1>min&&b2>=max)
        {

            if(n->buildingNum<b1)
            {
                BuildingsInRange(n->r,min,max,b1,b2);
            }
            else if(n->buildingNum==b2)
            {
                bNum_search[search_counter]=n->buildingNum;
                exTime_search[search_counter]=n->executed_time;
                totalTime_search[search_counter]=n->total_time;
                search_counter++;
                BuildingsInRange(n->l,min,max,b1,b2);
            }
            else if(n->buildingNum==b1)
            {
                bNum_search[search_counter]=n->buildingNum;
                exTime_search[search_counter]=n->executed_time;
                totalTime_search[search_counter]=n->total_time;
                search_counter++;
                BuildingsInRange(n->r,min,max,b1,b2);
            }
            else if(n->buildingNum>b1 && n->buildingNum<b2)
            {
                BuildingsInRange(n->l,min,max,b1,b2);
                bNum_search[search_counter]=n->buildingNum;
                exTime_search[search_counter]=n->executed_time;
                totalTime_search[search_counter]=n->total_time;
                search_counter++;
                BuildingsInRange(n->r,min,max,b1,b2);
                
            }
            
        }
        //if B1 is the LEFT MOST leaf child of the RBT
        else if(b1<=min&&b2<=max)
        {
            
            if(n->buildingNum>b2)
            {
                BuildingsInRange(n->l,min,max,b1,b2);
            }
            else if(n->buildingNum==b1)
            {
                bNum_search[search_counter]=n->buildingNum;
                exTime_search[search_counter]=n->executed_time;
                totalTime_search[search_counter]=n->total_time;
                search_counter++;
                BuildingsInRange(n->r,min,max,b1,b2);
            }
            else if(n->buildingNum==b2)
            {
                bNum_search[search_counter]=n->buildingNum;
                exTime_search[search_counter]=n->executed_time;
                totalTime_search[search_counter]=n->total_time;
                search_counter++;
                BuildingsInRange(n->l,min,max,b1,b2);
            }
            else if(n->buildingNum>b1&& n->buildingNum<b2)
            {
                BuildingsInRange(n->l,min,max,b1,b2);
                bNum_search[search_counter]=n->buildingNum;
                exTime_search[search_counter]=n->executed_time;
                totalTime_search[search_counter]=n->total_time;
                search_counter++;
                BuildingsInRange(n->r,min,max,b1,b2);
                
            }
            
           
        }
        //If neither b1 nor b2 are the extreme leaf nodes in the tree
        else if(b1>min&&b2<max)
        {
            
            if(n->buildingNum>b1&& n->buildingNum<b2)
            {
                BuildingsInRange(n->l,min,max,b1,b2);
                bNum_search[search_counter]=n->buildingNum;
                exTime_search[search_counter]=n->executed_time;
                totalTime_search[search_counter]=n->total_time;
                search_counter++;
                BuildingsInRange(n->r,min,max,b1,b2);
                
            }
            else if(n->buildingNum==b2)
            {
                bNum_search[search_counter]=n->buildingNum;
                exTime_search[search_counter]=n->executed_time;
                totalTime_search[search_counter]=n->total_time;
                search_counter++;
                BuildingsInRange(n->l,min,max,b1,b2);
            }
            else if(n->buildingNum==b1)
            {
                bNum_search[search_counter]=n->buildingNum;
                exTime_search[search_counter]=n->executed_time;
                totalTime_search[search_counter]=n->total_time;
                search_counter++;
                BuildingsInRange(n->r,min,max,b1,b2);
            }
            else if(n->buildingNum>b2)
            {
                BuildingsInRange(n->l,min,max,b1,b2);
            }
            else if(n->buildingNum<b1)
            {
                BuildingsInRange(n->r,min,max,b1,b2);
            }
            
        }
    }
}
//UPDATES THE EXECUTED TIME FOR BUILDING IN THE RBT
void updateExecutedTimeRBT(NODE root, node *BuildingRecord)
{
    
    if (root->buildingNum == BuildingRecord[0].buildingNum){
        root->executed_time=BuildingRecord[0].executed_time;
    }
    else if (BuildingRecord[0].buildingNum >= root->buildingNum){
        updateExecutedTimeRBT(root->r,BuildingRecord);
    }
    else{
        updateExecutedTimeRBT(root->l,BuildingRecord);
    }
    
}
//HANDLES THE PRINT(Bnum) FUNCTION, WRITES (0,0,0) in file in case the specified Bnum is not found in the RBT
void Print_B_Info(NODE root, int bNum, int indicator)
{
    
    ofstream oFile;
    oFile.open("output_file.txt",ios::app);
    //In case of an empty heap
    if(heap_size==0){
        oFile<<"(0,0,0)\n";
    }
    else{
        
        if(root==NULLPTR)  {
        }
        else{
            if ( root->buildingNum == bNum)
            {
                oFile<<"(";
                oFile<<root->buildingNum<<",";
                oFile<<root->executed_time<<",";
                oFile<<root->total_time;
                oFile<<")\n";
                indicator=1;
            }
            else if (bNum < root->buildingNum)
                
            {
                if(root->l!=NULLPTR)
                    Print_B_Info(root->l, bNum,indicator);
                else
                {
                    oFile<<"(0,0,0)\n";
                }
            }
            
            else if (bNum >= root->buildingNum)
            {
                if(root->r!=NULLPTR)
                    Print_B_Info(root->r, bNum,indicator);
                else
                {
                    oFile<<"(0,0,0)\n";
                    oFile.close();
                }
                
            }
            
            
        }
    }
}


//PRINTS INFORMATION OF ALL THE BUILDINGS THAT ARE WITHIN RANGE FROM b1 and b2 by writing the elements from the temp arrays to the outputfile.
int Print_B_In_Range(NODE root,int flag,int b1,int b2)
{
    ofstream oFile;
    oFile.open("output_file.txt",std::ios::app);
    NODE i = find_minRBT(root);
    NODE j = find_maxRBT(root);
    if(heap_size==0){
        oFile<<"(0,0,0)\n";
    }
    if(b2<i->buildingNum||b1>j->buildingNum)
    {
        
    }
    else
    {
        search_counter=0;
        //Calling BuildingsInRange() function
        BuildingsInRange(root,i->buildingNum,j->buildingNum,b1,b2);
        int queue_size=search_counter;
        //Print building info from temporary arrays to the file
        for(int i=0;i<queue_size;i++)
        {
            flag=1;
            oFile<<"(";
            oFile<<bNum_search[i]<<",";
            oFile<<exTime_search[i]<<",";
            oFile<<totalTime_search[i];
            oFile<<")";
            //Places ',' in the output file"
            if(i<(queue_size-1))
                oFile<<",";
            //Places new line in the output file"
            if(i==(queue_size-1))
                oFile<<"\n";
        }
        oFile.close();
    }
    return flag;
}
//Function to perform left rotation
void rotateLeft(NODE *root, NODE n)
{
    NODE j = NULL;
    j= n->r;
    n->r = j->l;
    if (j->l != NULLPTR)
        j->l->parent = n;
    j->parent = n->parent;
    if (n->parent == NULLPTR)
        *root = j;
    else if (n->parent->l != n)
        n->parent->r = j;
    else
        n->parent->l = j;
    j->l = n;
    n->parent = j;
}
//Function to perform right rotation
void rotateRight(NODE *root, NODE n) {
    NODE i = NULL;
    i= n->l;
    n->l = i->r;
    if (i->r != NULLPTR)
        i->r->parent = n;
    i->parent = n->parent;
    if (n->parent == NULLPTR)
        *root = i;
    else if (n->parent->l != n)
        n->parent->r = i;
    else
        n->parent->l = i;
    i->r = n;
    n->parent = i;
}
//Function to fix the RBT after a node is inserted in RBT
void fixInsertRBT(NODE *root, NODE n) {
    while (n->parent->colour == RED) {
        if (n->parent == n->parent->parent->l) {
            NODE j = n->parent->parent->r;
            if (j->colour != RED) {
                if (n == n->parent->r) {
                    n = n->parent;
                    rotateLeft(root,n);
                }
                n->parent->colour = BLACK;
                n->parent->parent->colour = RED;
                rotateRight(root,n->parent->parent);
            }
            else{
                n->parent->colour = BLACK;
                j->colour = BLACK;
                n->parent->parent->colour = RED;
                n = n->parent->parent;
            }

        }
        else {
            NODE j = n->parent->parent->l;
            if (j->colour != RED) {
                if (n == n->parent->l) {
                    n = n->parent;
                    rotateRight(root,n);
                }
                n->parent->colour = BLACK;
                n->parent->parent->colour = RED;
                rotateLeft(root,n->parent->parent);
                
            }
            else{
                n->parent->colour = BLACK;
                j->colour = BLACK;
                n->parent->parent->colour = RED;
                n = n->parent->parent;
            }
            
            
        }
    }
    (*root)->colour = BLACK;
}
//Insert element in the RBT
NODE insertRBT(NODE *root, int bNum, int ttime) {
    
    NODE n = (NODE) malloc(sizeof(struct node));
    n->buildingNum = bNum;
    n->executed_time=0;
    n->total_time=ttime;
    NODE i = *root;
    NODE j = NULLPTR;
    while (i != NULLPTR) {
        j = i;
        if (n->buildingNum >= i->buildingNum)
            i = i->r;
        else
            i = i->l;
    }
    n->parent = j;
    if (j == NULLPTR)
        *root = n;
    else if (n->buildingNum < j->buildingNum)
        j->l = n;
    else
        j->r = n;
    n->l = NULLPTR;
    n->r = NULLPTR;
    n->colour = RED;
    fixInsertRBT(root,n);
    return *root;
}

void transplantRBT(NODE *root, NODE u, NODE v) {
    if (u->parent == NULLPTR)
        *root = v;
    else if (u == u->parent->l)
        u->parent->l = v;
    else
        u->parent->r = v;
    v->parent = u->parent;
}
//Fix the RBT after a node is deleted
void fixDeleteRBT(NODE *root, NODE i) {
    while (i != *root && i->colour == BLACK) {
        if (i == i->parent->l) {
            NODE q = i->parent->r;
            if (q->colour == RED) {
                q->colour = BLACK;
                i->parent->colour = RED;
                rotateLeft(root,i->parent);
                q = i->parent->r;
            }
            if (q->l->colour == BLACK && q->r->colour == BLACK) {
                q->colour = RED;
                i = i->parent;
            }
            else {
                if (q->r->colour == BLACK) {
                    q->l->colour = BLACK;
                    q->colour = RED;
                    rotateRight(root,q);
                    q = i->parent->r;
                }
                q->colour = i->parent->colour;
                i->parent->colour = BLACK;
                q->r->colour = BLACK;
                rotateLeft(root,i->parent);
                i = *root;
            }
        }
        else {
            NODE q = i->parent->l;
            if (q->colour == RED) {
                q->colour = BLACK;
                i->parent->colour = RED;
                rotateRight(root,i->parent);
                q = i->parent->l;
            }
            if (q->l->colour == BLACK && q->r->colour == BLACK) {
                q->colour = RED;
                i = i->parent;
            }
            else {
                if (q->l->colour == BLACK) {
                    q->r->colour = BLACK;
                    q->colour = RED;
                    rotateLeft(root,q);
                    q = i->parent->l;
                }
                q->colour = i->parent->colour;
                i->parent->colour = BLACK;
                q->l->colour = BLACK;
                rotateRight(root,i->parent);
                i = *root;
            }
        }
    }
    i->colour = BLACK;
}
//Performs Deletion of a node in RBT, it calls the fixDeleteRBT function
NODE deleteRBT(NODE *root, int z) {
    NODE Z = search_RBT(*root, z);
    if (Z == NULLPTR) {
        
        return nullptr;
    }
    NODE j = NULL;
    j=Z;
    int yoc = j->colour;
    NODE i;
    if (Z->l == NULLPTR) {
        i = Z->r;
        transplantRBT(root,Z,Z->r);
    }
    else if (Z->r == NULLPTR) {
        i = Z->l;
        transplantRBT(root,Z,Z->l);
    }
    else {
        j = find_minRBT(Z->r);
        yoc = j->colour;
        i = j->r;
        if (j->parent == Z)
            i->parent = j;
        else {
            transplantRBT(root,j,j->r);
            j->r = Z->r;
            j->r->parent = j;
        }
        transplantRBT(root,Z,j);
        j->l = Z->l;
        j->l->parent = j;
        j->colour = Z->colour;
    }
    if (yoc == BLACK)
        fixDeleteRBT(root,i);
    return *root;
}



//returns the parent a element in the heap
int parent(int i){
    return (i-1)/2;
}
//Inserts a node in the Heap, after insertion the heap is altered so that it retains it's properties
void insertKey(node *buildingRecord,int buildingNum, int total_time)
{
    if (heap_size == capacity)
    {
        cout<< "COULD NOT INSERT KEY DUE TO OVERFLOW";
        return;
    }
    //Insert element at the end of the heap
    heap_size++;
    int i = heap_size - 1;
    buildingRecord[i].buildingNum = buildingNum;
    buildingRecord[i].executed_time=0;
    buildingRecord[i].total_time=total_time;
    
    while (i != 0 && buildingRecord[parent(i)].executed_time >= buildingRecord[i].executed_time)
    {
        
        node temp=buildingRecord[i];
        buildingRecord[i]=buildingRecord[parent(i)];
        buildingRecord[parent(i)]=temp;
        if(buildingRecord[parent(i)].executed_time==buildingRecord[i].executed_time){
            if(buildingRecord[parent(i)].buildingNum>buildingRecord[i].buildingNum){
                node temp2=buildingRecord[i];
                buildingRecord[i]=buildingRecord[parent(i)];
                buildingRecord[parent(i)]=temp2;
                i=parent(i);
            }
        }
        else{
            i=parent(i);
        }
    }
}

//Prints the current heap
void print_heap(node *buildingRecord){
    for(int i=0;i<heap_size;i++){
        cout<<buildingRecord[i].buildingNum<<" "<<buildingRecord[i].executed_time<<" "<<buildingRecord[i].total_time<<"\n";
    }
    
    
    
}
//Heapifies the Heap, also takes care of the conditions when the parent and it's children have the same execution time
void heapify(node *buildingRecord,int n,int i){
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    //If the ex_time value of parent and both it's children are the same
    if(r < n && buildingRecord[r].executed_time == buildingRecord[l].executed_time && buildingRecord[r].executed_time == buildingRecord[i].executed_time ){
        if(buildingRecord[r].buildingNum<buildingRecord[l].buildingNum && buildingRecord[r].buildingNum<buildingRecord[i].buildingNum){
            smallest=r;
        }
        else if(buildingRecord[l].buildingNum<buildingRecord[r].buildingNum && buildingRecord[l].buildingNum<buildingRecord[i].buildingNum){
            smallest=l;
        }
        else{
            smallest=i;
        }
    }
    //    //If the ex_time value of parent and it's right child is the same
    else if(r<n && buildingRecord[r].executed_time == buildingRecord[i].executed_time){
        if(buildingRecord[r].buildingNum<buildingRecord[i].buildingNum){
            smallest=r;
        }
        else{
            smallest=i;
        }
    }
    //    //If the ex_time value of parent and it's left child is the same
    else if(l<n && buildingRecord[l].executed_time == buildingRecord[i].executed_time){
        if(buildingRecord[l].buildingNum<buildingRecord[i].buildingNum){
            smallest=l;
        }
        else{
            smallest=i;
        }
    }

    if(r<n && buildingRecord[r].executed_time<buildingRecord[smallest].executed_time && buildingRecord[l].executed_time<buildingRecord[smallest].executed_time && buildingRecord[l].executed_time==buildingRecord[r].executed_time){
        if(buildingRecord[l].buildingNum>buildingRecord[r].buildingNum){
            smallest=r;
        }
        else{
            smallest=l;
        }
        
    }
    else if (l < n && buildingRecord[l].executed_time < buildingRecord[smallest].executed_time )
        smallest = l;
    
    else if(r < n && buildingRecord[r].executed_time < buildingRecord[smallest].executed_time)
        smallest = r;
    
    if (smallest != i) {
        //swap the heap child with it's parent
        swap(buildingRecord[i], buildingRecord[smallest]);
        
        heapify(buildingRecord, n, smallest);
    }
}
//Function that writes the building number and the global counter in the output file when a building is finished with it's construction
void print_delete(node* buildingRecord){
    ofstream otp;
    otp.open("output_file.txt",ios::app);
    otp<<"(";
    otp<<buildingRecord[0].buildingNum;
    otp<<",";
    otp<<global_counter+1;
    otp<<")";
    otp<<"\n";
}

//Deletes the topmost element(root) of the heap and heapify is called after deletion
int delete_Root(node *buildingRecord)
{
    if(heap_size==1){
        //cout<<"\nDELETED ELEMENT="<<buildingRecord[0].buildingNum<<" GLOBAL COUNTER="<<global_counter+1;
        print_delete(buildingRecord);
        heap_size=0;
        return buildingRecord[0].executed_time;
    }
    
    node lastElement = buildingRecord[heap_size-1];
    //cout<<"\nDELETED ELEMENT="<<buildingRecord[0].buildingNum<<" GLOBAL COUNTER="<<global_counter+1;
    
    print_delete(buildingRecord);   //Calls the delete function which writes buildings completed in the output file
    buildingRecord[0] = lastElement;
    
    heap_size = heap_size - 1;
    
    heapify(buildingRecord, heap_size, 0);
    return 1;
    
}

//Construction function which is called by the main driver function get_Input(). It updates the execution time of the building being worked on each day and returns a boolean value which signifies that if we can start working on other buildings.Also calls delete function for the building when it gets completed. Also inserts the pending buildings in the heap when the logic allows.
bool construct(node *buildingRecord, node *tree){
    //Update execution time by 1 day
    buildingRecord[0].executed_time=buildingRecord[0].executed_time+1;
    //If the building and finished execution
    if(buildingRecord[0].executed_time==buildingRecord[0].total_time){
        

        //Give precedence to input command before deletion if there exists a print statement
        if(goToPrint==1 && counter[counter_itr]==global_counter+1){
            flag=1;
            return false;
        }
        else{
            root=deleteRBT(&root, buildingRecord[0].buildingNum);
            delete_Root(buildingRecord);
        }
        return true;
    }
    //If the building completes 5 consecutive days of work, we insert the pending buildings in the min heap
    else if(buildingRecord[0].executed_time %5 ==0 ){
        updateExecutedTimeRBT(root, buildingRecord);
        heapify(buildingRecord,heap_size,0);
        if(pending_bnum.size()>0){
            for(int i=0;i!=pending_bnum.size();i++){
                root=insertRBT(&root, pending_bnum[i], pending_time[i]);
                insertKey(buildingRecord, pending_bnum[i], pending_time[i]);
                
            }
            pending_bnum.clear();
            pending_time.clear();
        }
        return true;
    }
    else{
        return false;
    }
}
//Parses the input from the input file. This is the main driver function. Calls the insertion functions for the RBT and the MinHeap and also calls the respective print commands.
void get_Input(node *buildingRecord){
    NODE tree = NULLPTR;
    int buildingNum, total_time;
    ifstream inFile(file_name);
    string one_line;
    ifstream inFileAgain(file_name);
    string one_lineAgain;
    //Reads the values of counters in the input file and store it in an array
    while(getline(inFile,one_line)){
        int c= stoi(one_line.substr(0,one_line.find(":")));
        counter[k]=c;
        k++;
    }
    inFile.close();
    //Keeps on reading file until the end and executes the respective commands for insertion/print
    while(getline(inFileAgain,one_lineAgain)){
        
        int found=one_lineAgain.find("Insert");
        if(found== string::npos){
            goToPrint=1;
        }
        else{
            goToPrint=0;
        }
        
        while(global_counter<counter[counter_itr] && counter_itr<k){
            if(heap_size==0){
                if(goToPrint==0){
                    global_counter++;
                }
                else{
                    global_counter=counter[counter_itr]+1;
                    break;
                }
            }
            else{
                goahead=construct(buildingRecord,tree);
                if(heap_size!=0){
                    updateExecutedTimeRBT(root,buildingRecord);
                    
                }
                global_counter++;
            }
            
        }
        if(goToPrint==0){
            int l=one_lineAgain.find(",");
            int l1=one_lineAgain.find("(");
            int length=l-l1-1;
            buildingNum=stoi(one_lineAgain.substr(one_lineAgain.find("(")+1,length));
            l=one_lineAgain.find(")");
            l1=one_lineAgain.find(",");
            length=l-l1-1;
            total_time=stoi(one_lineAgain.substr(one_lineAgain.find(",")+1,length));
            //If construct function returns true, we can start working on next building in the minHeap
            if(goahead){
                
                if(heap_size==0){
                    NODE tree = NULLPTR;
                    root=insertRBT(&tree, buildingNum, total_time);
                }
                else{
                    root=insertRBT(&root, buildingNum, total_time);
                }
                insertKey(buildingRecord, buildingNum, total_time);
                goahead=construct(buildingRecord,tree);
                updateExecutedTimeRBT(root,buildingRecord);
                global_counter++;
                
            }
            // If construct returns false, we store the buildings info from the input file to a pending buildings vector
            else{
                pending_time.push_back(total_time);
                pending_bnum.push_back(buildingNum);
                goahead=construct(buildingRecord,tree);
                updateExecutedTimeRBT(root,buildingRecord);
                global_counter++;
            }
        }
        //If its a Print Command
        else if(goToPrint==1){
            int count_para=0;
            for(int i=0;i!=one_lineAgain.size();i++){
                if(one_lineAgain[i]==','){
                    count_para++;
                }
            }
            //If it's PrintBuilding(bnum) function
            if(count_para==0){
                int pos1=one_lineAgain.find("(");
                int pos2=one_lineAgain.find(")");
                int length=pos1-pos2-1;
                int b1=stoi(one_lineAgain.substr(one_lineAgain.find("(")+1,length));
                Print_B_Info(root, b1, 0);
            }
            //If it's a PrintBuilding(bnum1, bnum2) function
            else if(count_para==1){
                int pos1=one_lineAgain.find(",");
                int pos2=one_lineAgain.find("(");
                int length=pos1-pos2-1;
                int b1=stoi(one_lineAgain.substr(one_lineAgain.find("(")+1,length));
                pos1=one_lineAgain.find(")");
                pos2=one_lineAgain.find(",");
                length=pos1-pos2-1;
                int b2=stoi(one_lineAgain.substr(one_lineAgain.find(",")+1,length));
                Print_B_In_Range(root,0,b1,b2);
            }
            //If the print command was given precedence over other commands(1st condition in construct function)
            if(flag==1){
                global_counter=global_counter-1;
                root=deleteRBT(&root, buildingRecord[0].buildingNum);
                delete_Root(buildingRecord);
                global_counter=global_counter+1;
            }
            flag=0;
            
        }
        counter_itr++;
        goToPrint=0;
    }
    //Finish construction of the remaining buildings in the heap after the file parsing is done
    while(heap_size!=0){
        goahead=construct(buildingRecord,tree);
        if(heap_size==0){
        }
        else{
            updateExecutedTimeRBT(root,buildingRecord);
        }
        global_counter++;
    }
}
//Main Function- Calls the driver function getInput();
int main(int argc, const char * argv[]) {
    file_name=argv[1];
    ofstream oFile("output_file.txt", ios::out|ios::trunc);
    NIL.r=NULLPTR;
    NIL.l=NULLPTR;
    NIL.parent=NULLPTR;
    NIL.colour = BLACK;
    struct node buildingRecord[2000];
    get_Input(buildingRecord);
    return 0;
}
