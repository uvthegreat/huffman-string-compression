#include <bits/stdc++.h>
using namespace std;


// creating node for structure of huffman tree
struct Node{
    char ch; //code of the character
    int freq; //frequency of the character
    Node *right, *left;

    Node(char ch1, int freq1, Node *r=NULL, Node *l=NULL){
        ch=ch1;
        freq=freq1;
        right=r;
        left=l;
    }
};

// creating a comperator for priority queue
struct comp{
    bool operator()(Node *a, Node *b){
        return a->freq>b->freq;
    }
};

Node *huffman_tree(string msg){
    // count frequency of each character and store it in unordered map;
    unordered_map<char, int> freq;
    for (char c : msg){
          freq[c]++;
    }
    
    // create a priority queue store the leaf node of tree
    // priority queue store elements in a container and the last element of the
    // container is the highest priority element in priority queue.
    // so to get highest frequency at the top of queue we need to give a 
    // comparator as bigger element first a>b this means bigger elements has higher priority 
    // and the go to last position of queue so get top element as lowest frequency;
    priority_queue<Node*, vector<Node*>, comp>pq;


    // creating a leaf node for every character and add it to the priority queue
    for(auto i : freq){
        Node* n = new Node(i.first, i.second);
        pq.push(n);
    }

    // creating huffman tree
    while(pq.size()!=1){
    // here take top two nodes from priority queue which has min freq
        Node*left = pq.top();
        pq.pop();
        Node*right = pq.top();
        pq.pop();

        int sum = left->freq + right->freq;

        // creating a parent node which contains the sum of frequencies of
        // left and right
        // here '\0' is the name of everynode which is not leaf node
        // as leaf node has their names but we also have to give some name to 
        // other internal nodes
        Node* parent = new Node('\0', sum, left, right);
        // pushing the created node again to priority_queue
        pq.push(parent);
    }

    // finally we are left with only one node in the priority queue which 
    //  is the root node of required huffman tree
    return pq.top();    
}

void encode(Node* root, string bit_code ,unordered_map<char, string>& huffman_table){
    if(root==NULL)return;

    // if we get to leaf node by recursion store the created bite code in map
    if(!root->left && !root->right){
        huffman_table[root->ch]= bit_code;
    }

    // traverse left and right node to get to leaf node and also 
    // on the way creating their bite codes
    encode(root->left, bit_code + "0", huffman_table);

    encode(root->right, bit_code + "1", huffman_table);

}
string decode(Node*root, int &index, string bit_code, string &decoded_msg){
    if(root==NULL) return decoded_msg;

    // append to decoded message if leaf node is found
    if(!root->left && !root->right){
        decoded_msg += root->ch;
        return decoded_msg;
    }

    index++;
    // traversing left if bit_code is 0 or right if bit_code is 1;
    if(bit_code[index]=='0'){
        decode(root->left, index, bit_code,decoded_msg);
    }else{
        decode(root->right, index, bit_code,decoded_msg);
    }  
    return decoded_msg;
}


int main()
{
    string msg = "abcdacad";
	
	// createing huffman tree from given msg
	Node* root = huffman_tree(msg);

	// Traverse the Huffman Tree and store Huffman Codes
	// in a map. this proces is made as a function called
    //  encode and Also prints them;
	unordered_map<char, string> huffmanCodes;
	encode(root, "", huffmanCodes);
    // encode function stores codes of each character in map called 
    // huffmanCodes;

	// printing Huffman Code of each Character of the msg
	cout << "Huffman Codes are :\n" << '\n';
	for (auto pair: huffmanCodes) {
		cout << pair.first << " " << pair.second << '\n';
	}

	// printing original msg
	cout << "\nOriginal string was :\n" << msg << '\n';
    cout << "size of original string in binary is : " <<msg.size()*8 ;

	// creating encoded msg
	string encoded_msg = "";
	for (char ch: msg) {
		encoded_msg += huffmanCodes[ch];
	}
    // printing encode msg
	cout << "\nEncoded string is :\n" << encoded_msg << '\n';
    cout << "size of original string in binary is : " <<encoded_msg.size();


    // decoding msg
    string decoded_msg = "";
    int index=-1;
    // in every iteration decode function decodes only one 
    // character decodes so to decode every character 
    // we need to traverse and call decode fucntion 
    // again and again;
    while(index<(int)encoded_msg.size()-1){
        decode(root, index, encoded_msg, decoded_msg);
    }
	cout << "\nDecoded string is: \n" << decoded_msg << endl;
    
    return 0;
}
