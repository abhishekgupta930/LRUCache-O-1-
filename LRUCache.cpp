class Node
{
    public:

    int key;	// Stores Key
    int value;	// Stores Value
    Node * next;	// points to next Node 
    Node * prev;	// points to previous Node

    Node(int key, int value)
    {
        this->key = key;
        this->value = value;
        next = NULL;
        prev = NULL;
    }
};

class DLinkList
{
    Node *start, *end;

    public:
        DLinkList()
        {
            start = NULL;
            end = NULL;
        }

    Node* addnode(int, int);
    void display();
    void deletenode(Node*);
    void pushToFront(Node*);
    int delLastNode();
};

Node *DLinkList::addnode(int key, int value)
{
    Node *newNode = new Node(key, value);

   	// We are adding at begining

   	// if it is first node
    if (start == NULL)
    {
        start = newNode;
        start->next = start->prev = NULL;
        end = start;
        return newNode;
    }

    newNode->next = start;
    newNode->prev = NULL;
    start->prev = newNode;
    start = newNode;

    return newNode;

}

void DLinkList::pushToFront(Node *keyAddr)
{
   	//cout<< "\nDeleting Node for rearrengement: " << keyAddr->key;

   	//If node is last Node
    if (start == end)
    {
       	// Do nothing
        return;
    }

    if (keyAddr == end)
    {
        end = keyAddr->prev;
        keyAddr->prev->next = keyAddr->next;
        keyAddr->next = start;
        keyAddr->prev = NULL;
        start->prev = keyAddr;
        start = keyAddr;
        return;
    }

    if (keyAddr == start)
    {
        return;
    }

    keyAddr->next->prev = keyAddr->prev;
    keyAddr->prev->next = keyAddr->next;
    keyAddr->next = start;
    keyAddr->prev = NULL;
    start->prev = keyAddr;
    start = keyAddr;

    return;
}

void DLinkList::deletenode(Node *keyAddr)
{
   	//cout<< "\nDeleting Node for rearrengement: " << keyAddr->key;

   	//If node is last Node
    if (start == end)
    {
        start = NULL;
        end = NULL;
       	//cout<< "\nDeleting last remaning node : " << keyAddr->key;
       	//delete (keyAddr);
        return;
    }

    if (keyAddr == end)
    {
        end = keyAddr->prev;
        keyAddr->prev->next = keyAddr->next;
        return;
    }

    if (keyAddr == start)
    {
        start = keyAddr->next;
        return;
    }

    keyAddr->next->prev = keyAddr->prev;
    keyAddr->prev->next = keyAddr->next;

   	//keyAddr = NULL;
   	//keyAddr->prev = NULL;
   	//keyAddr->prev = NULL;

    delete(keyAddr);
    return;
}

int DLinkList::delLastNode(void)
{
   	// cout <<"\n Deleting Tail Node";

    Node *trav = start;
    int key;
   	// If it is the last Node 
    if (start == end)
    {
        key = start->key;
        start = NULL;
        end = NULL;
        return key;
    }

   	// reach to the end
    while (trav != end)
    {
        trav = trav->next;
    }


   	//Get the key
    key = trav->key;

   	//Adjust the pointers
    trav->prev->next = NULL;
    end = trav->prev;

   	//Free Memeory Location
    delete(trav);
    return key;
}

class LRUCache
{
    public:

   	// Doubly LinkedList STL
    DLinkList myList;

   	// Unordered Map in STL is implemented as hash Table
    unordered_map<int, Node*> umap;

   	// MAX size of LRU Cache
    int size;

    LRUCache(int capacity)
    {
        myList = DLinkList();
        size = capacity;

    }

   	// Read the entry from Cache

    int get(int key)
    {
       	// Key is present in Cache
       	//cout << " searching for key : " << key;

        if (umap.find(key) != umap.end())
        {
           	// Take the key out of doubly linkedlist and 
           	// Update position in Doubly linked List i.e
           	// place it in the front. 
           	// Finally return the value coressponding to the key 

           	//Remove key;
            Node *keyAddr = umap[key];
            int value = keyAddr->value;
            myList.pushToFront(keyAddr);
            return value;
        }
        else
        {
           	// Entry not found in Cache/Map
            return -1;
        }
    }

    void put(int key, int value)
    {
       	// If Linklist is full. Remove the element from
       	// the back which is going to be least recently used.
        if (umap.size() == size && umap.find(key) == umap.end())
        {
           	//Remove last element from the queue as Cache is full
            int key = myList.delLastNode();
            umap.erase(key);

        }

       	// If key already exists 

        if (umap.find(key) != umap.end())
        {
            
            
            /*
            Node *keyAddr = umap[key];
            umap.erase(key);
            myList.deletenode(keyAddr);

            keyAddr = myList.addnode(key, value);
            umap.insert({ key, keyAddr });
            */
            
            Node *keyAddr = umap[key];
            keyAddr->value = value;
            myList.pushToFront(keyAddr);


            
            

        }
        else
        {
           	// Add the entry in fromt of linkedlist
            Node *keyAddr = myList.addnode(key, value);
           	// Add at the key value pair in map
            umap.insert({ key, keyAddr });

        }
    }
};
