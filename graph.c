
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

#define INFINITY -1
/**
typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;
 */
int g_size = 0;
int max_index = 0;
pnode graph;
char buff;
pnode *queue;


void free_edge_pointers(pnode *a_node){
    /**
     * free the memory of nodes in graph
     */
    pedge curr = (*a_node)->edges;
    if(*a_node){
        while(curr){
            pedge temp = curr->next;
            free(curr);
            curr = temp;
        }
    }
    
}

void free_graph_pointers(pnode *graph){
    /**
     * free the memory of nodes in graph
     */
    pnode curr = *graph;
    if(*graph){
        while(curr){
            pnode temp = curr->next;
            free_edge_pointers(&curr);
            free(curr);
            curr = temp;
        }
    }
    
}


void build_graph_cmd(pnode *head){
    /**
     * free the memory of nodes in the old graph
     */
    free_graph_pointers(head);
    /**
     *  calc size of graph and set graph to head
     */
    int size_of_graph;
    scanf("%d", &size_of_graph);
    g_size = size_of_graph;
    if(g_size > 0){
        pnode first_node = (pnode)malloc(sizeof(node));

        pnode curr = first_node;
        for(int i=0; i<g_size-1; i++){
            curr->node_num = i;
            curr->edges = NULL;
            curr->next = (pnode)malloc(sizeof(node));
            curr = curr->next;
        }
        curr->node_num = g_size-1;
        curr->edges = NULL;
        curr->next = NULL;
        *head = first_node;
    }
}

void insert_node_cmd(pnode *head){
    int node_index = 0;
    scanf("%c", &buff);
    while((buff<=57 && buff >= 48)){
        node_index *= 10;
        node_index += (buff-48);
        scanf("%c", &buff);
    }
    pnode curr = *head;
    pnode node_to_add;
    if(node_index>max_index){
        max_index = node_index;
    }
    while(curr){
        if(curr->node_num == node_index){
            node_to_add = curr;
        }
        curr = curr->next;
    }
    free_edge_pointers(&node_to_add);
    node_to_add->edges = NULL;
    while(buff == ' '){
        scanf("%c", &buff);
        if((buff<=57 && buff >= 48)){
            int dest = 0;
            while((buff<=57 && buff >= 48)){
                dest *= 10;
                dest += (buff-48);
                scanf("%c", &buff);
            }
            scanf("%c", &buff);
            int weights = 0;
            while((buff<=57 && buff >= 48)){
                weights *= 10;
                weights += (buff-48);
                scanf("%c", &buff);
            }
            curr = *head;
            while(curr){
                if(curr->node_num == dest){
                    pedge new_edge = (pedge)malloc(sizeof(edge));
                    new_edge->next = node_to_add->edges;
                    new_edge->endpoint = curr;
                    new_edge->weight = weights;
                    node_to_add->edges = new_edge;
                }
                curr = curr->next;
            }
        }
    }
}

void make_new_node(pnode *head){
    int node_index = 0;
    scanf("%c", &buff);
    while((buff<=57 && buff >= 48)){
        node_index *= 10;
        node_index += (buff-48);
        scanf("%c", &buff);
    }
    pnode curr = *head;
    pnode node_to_add;
    if(node_index>max_index){
        max_index = node_index;
    }
    int found = 0; 
    while(curr){
        if(curr->node_num == node_index){
            node_to_add = curr;
            free_edge_pointers(&node_to_add);
            node_to_add->edges = NULL;
            found = 1;
        }
        curr = curr->next;
    }
    if(found == 0){
        node_to_add = (pnode)malloc(sizeof(node));
        node_to_add->edges = NULL;
        node_to_add->node_num = node_index;
        node_to_add->next = (*head);
        *head = node_to_add;
        g_size++;
    }
    
    while(buff == ' '){
        scanf("%c", &buff);
        if((buff<=57 && buff >= 48)){
            int dest = 0;
            while((buff<=57 && buff >= 48)){
                dest *= 10;
                dest += (buff-48);
                scanf("%c", &buff);
            }
            scanf("%c", &buff);
            int weights = 0;
            while((buff<=57 && buff >= 48)){
                weights *= 10;
                weights += (buff-48);
                scanf("%c", &buff);
            }
            curr = *head;
            while(curr){
                if(curr->node_num == dest){
                    pedge new_edge = (pedge)malloc(sizeof(edge));
                    new_edge->next = node_to_add->edges;
                    new_edge->endpoint = curr;
                    new_edge->weight = weights;
                    node_to_add->edges = new_edge;
                }
                curr = curr->next;
            }
        }
    }
}

void delete_node_cmd(pnode *head){
    int node_index = 0;
    scanf("%c", &buff);
    while((buff<=57 && buff >= 48)){
        node_index *= 10;
        node_index += (buff-48);
        scanf("%c", &buff);
    }
    pnode prev = NULL;
    pnode curr = *head;
    pnode node_to_del;
    int found = 0; 
    while(curr){
        if(curr->node_num == node_index){
            node_to_del = curr;
            found = 1;
            if(prev){
                prev->next = curr->next;
            }
            else{
                *head = curr->next;
            }
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    if(found == 0){
        printf("not exist \n");
    }
    else{
        free_edge_pointers(&node_to_del);
        node_to_del->edges = NULL;
        g_size--;
        curr = *head;
        while (curr)
        {
            pedge prev_edge = NULL;
            pedge c_edge = curr->edges;
            while (c_edge)
            {
                if(c_edge->endpoint == node_to_del){
                    if(prev_edge){
                        prev_edge->next = c_edge->next;
                    }
                    else{
                        curr->edges = c_edge->next;
                    }

                    free(c_edge);
                    break;
                }
                prev_edge = c_edge;
                c_edge = c_edge->next;
            }
            curr = curr->next;
        }
        free(node_to_del);
    }
    
}
void printGraph_cmd(pnode head){
    printf("----GRAPH----\n");
    pnode curr = head;
    int this_size = 0;
    while(curr){
        printf("node id: %d \n", curr->node_num);
        this_size++;
        pedge edge_to_show = curr->edges;
        while(edge_to_show){
            printf("edge from %d to %d with cost %d \n",curr->node_num ,edge_to_show->endpoint->node_num, edge_to_show->weight);
            edge_to_show = edge_to_show->next;
        }
        
        curr = curr->next;
    }
    printf("size is %d\n", g_size);
    printf("place in memory: %p\n", head);
}

void deleteGraph_cmd(pnode* head){
    free_graph_pointers(head);
    *head = NULL;
}

void shortsPath_cmd(pnode head){
    /*
    calc the shortest path using dikjstra algorithem for shortest path
    */
    int *dist = (int*)malloc(sizeof(int)*max_index + 1);
    int *visited = (int*)malloc(sizeof(int)*max_index + 1);
    queue =  (pnode*)malloc(sizeof(node)*g_size*2);
    int first = 0;
    int last = 0;
    int src = 0;

    for(int i=0; i<max_index+1;i++){
        dist[i] = INFINITY;
        visited[i] = 0;
    }

    scanf("%c", &buff);
    while((buff<=57 && buff >= 48)){
        src *= 10;
        src += (buff-48);
        scanf("%c", &buff);
    }

    int dst = 0;
    buff = '0';
    while((buff<=57 && buff >= 48)){
        dst *= 10;
        dst += (buff-48);
        scanf("%c", &buff);
    }
    
    pnode src_node;

    pnode curr = head;
    while(curr){
        if(curr->node_num == src){
            src_node = curr;
        }
        curr = curr->next;
    }
    curr = head;
    while(curr){
        if(curr->node_num == dst){
        }
        curr = curr->next;
    }

    queue[first] = src_node;
    dist[src] = 0;
    visited[src] = 1;
    last++;
    while (first < last)
    {   
        pnode out_node = queue[first];
        first++;
        pedge node_edges = out_node->edges;
        while (node_edges)
        {   
            if(visited[node_edges->endpoint->node_num] == 0){
                queue[last] = node_edges->endpoint;
                visited[node_edges->endpoint->node_num] = 1;
                last++;
            }
            if(dist[out_node->node_num] == INFINITY){
                dist[node_edges->endpoint->node_num] = dist[node_edges->endpoint->node_num];
            }
            else if(dist[node_edges->endpoint->node_num] == INFINITY){
                dist[node_edges->endpoint->node_num] = dist[out_node->node_num]+node_edges->weight;
            }
            else if(dist[out_node->node_num]+node_edges->weight < dist[node_edges->endpoint->node_num]){
                dist[node_edges->endpoint->node_num] = dist[out_node->node_num]+node_edges->weight;
            }
            node_edges = node_edges->next;
        }
        
    }
    printf("Dijsktra shortest path: %d \n", dist[dst]);
    free(queue);
    free(visited);
    free(dist);
}

int SP_with_index(pnode head, int from_node, int to_node){
        /*
    calc the shortest path using dikjstra algorithem for shortest path
    */
    int *dist = (int*)malloc(sizeof(int)*max_index + 1);
    int *visited = (int*)malloc(sizeof(int)*max_index + 1);
    queue =  (pnode*)malloc(sizeof(node)*g_size*2);
    int first = 0;
    int last = 0;
    int src = from_node;

    for(int i=0; i<max_index+1;i++){
        dist[i] = INFINITY;
        visited[i] = 0;
    }

    int dst = to_node;
    
    pnode src_node;

    pnode curr = head;
    while(curr){
        if(curr->node_num == src){
            src_node = curr;
        }
        curr = curr->next;
    }
    curr = head;
    while(curr){
        if(curr->node_num == dst){
        }
        curr = curr->next;
    }

    queue[first] = src_node;
    dist[src] = 0;
    visited[src] = 1;
    last++;

    while (first < last)
    {   
        pnode out_node = queue[first];
        first++;
        pedge node_edges = out_node->edges;
        while (node_edges)
        {   
            if(visited[node_edges->endpoint->node_num] == 0){
                queue[last] = node_edges->endpoint;
                visited[node_edges->endpoint->node_num] = 1;
                last++;
            }
            if(dist[out_node->node_num] == INFINITY){
                dist[node_edges->endpoint->node_num] = dist[node_edges->endpoint->node_num];
            }
            else if(dist[node_edges->endpoint->node_num] == INFINITY){
                dist[node_edges->endpoint->node_num] = dist[out_node->node_num]+node_edges->weight;
            }
            else if(dist[out_node->node_num]+node_edges->weight < dist[node_edges->endpoint->node_num]){
                dist[node_edges->endpoint->node_num] = dist[out_node->node_num]+node_edges->weight;
            }
            node_edges = node_edges->next;
        }
        
    }
    int final_dist = dist[dst];
    free(queue);
    free(visited);
    free(dist);
    return final_dist;
}

//function to swap the variables
void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
int tsp_sum=-1;
//permutation function
void permutation(int arr[6], int start, int end, pnode head)
{
    if(start==end)
    {
        int sum = 0;
        int set_to_inf = 0;
        for(int i=0; i<end; i++){
            int p_cost = SP_with_index(head, arr[i], arr[i+1]);
            if(p_cost == -1){
                set_to_inf = 1;
                sum = -1;
            }
            if(set_to_inf == 0){
                sum+=p_cost;
            }
            
        }
        if(sum<=tsp_sum || tsp_sum == -1){
            if(sum != -1){
               tsp_sum = sum; 
            }
        }
        return;
    }
    int i;
    for(i=start;i<=end;i++)
    {
        //swapping numbers
        swap((arr+i), (arr+start));
        //fixing one first digit
        //and calling permutation on
        //the rest of the digits
        permutation(arr, start+1, end, head);
        swap((arr+i), (arr+start));
    }
}

void TSP_cmd(pnode head){
    /*
    get all permotsion and calc their path cost.
    return the minimum
    */
    int citys[6] = {-1,-1,-1,-1,-1,-1};
    int city_num = 0;
    int amount = 0;
    scanf("%c", &buff);
    while((buff<=57 && buff >= 48)){
        amount *= 10;
        amount += (buff-48);
        scanf("%c", &buff);
    }
    int runner = 0;
    while(buff == ' '){
        scanf("%c", &buff);
        if((buff<=57 && buff >= 48)){
            city_num = 0;
            while((buff<=57 && buff >= 48)){
                city_num *= 10;
                city_num += (buff-48);
                scanf("%c", &buff);
            }
        }

        if(buff == ' ' || buff == '\n' ){
            citys[runner] = city_num;
            runner++;
        }
        
    }
    tsp_sum = -1;
    permutation(citys, 0,amount-1, head);
    printf("TSP shortest path: %d \n",tsp_sum);
}

int main(){
    scanf("%c", &buff); 
    while(buff != '\n'){
        if(buff != 'A' && buff != 'n' && buff != 'B' && buff != 'D' && buff != 'S' && buff != 'T'){
           scanf("%c", &buff); 
        }
        if(buff == 'A'){
            scanf("%c", &buff);
            build_graph_cmd(&graph);
            scanf("%c", &buff);
            scanf("%c", &buff);
        }
        if(buff == 'n'){
            scanf("%c", &buff);
            insert_node_cmd(&graph);
        }

        if(buff == 'B'){
            scanf("%c", &buff);
            make_new_node(&graph);
        }
        if(buff == 'D'){
            scanf("%c", &buff);
            delete_node_cmd(&graph);
        }
        if(buff == 'S'){
            scanf("%c", &buff);
            shortsPath_cmd(graph);
        }
        if(buff == 'T'){
            scanf("%c", &buff);
            TSP_cmd(graph);
        }
    }
    free_graph_pointers(&graph);
}
