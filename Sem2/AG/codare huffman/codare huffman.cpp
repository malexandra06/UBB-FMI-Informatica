#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <queue>
#include <map>

using namespace std;
ifstream in("input.txt");
ofstream out("output.txt");


struct Node {
    char car;
    int frecv;
    Node* st;
    Node* dr;

    Node(char ch, int freq) {
        car = ch;
        frecv = freq;
        st = nullptr;
        dr = nullptr;
    }

    Node(Node* l, Node* r) {
        car = '\0';
        frecv = l->frecv + r->frecv;
        st = l;
        dr = r;
    }
};

struct Compare {
    bool operator()(Node* l, Node* r) {
        if (l->frecv == r->frecv)
            return l->car > r->car;
        return l->frecv > r->frecv;
    }
};

void generateCodes(Node* root, string code, map<char, string>& codes) {
    if (root == nullptr)
        return;

    if (root->car != '\0') {
        codes[root->car] = code;
    }

    generateCodes(root->st, code + "0", codes);
    generateCodes(root->dr, code + "1", codes);
}

map<char, int> huffmanEncoding(const string& text, map<char, string>& codes) {
    map<char, int> frequencies;

    for (char ch : text) {
        frequencies[ch]++;
    }

    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (const auto& pair : frequencies) {
        Node* newNode = new Node(pair.first, pair.second);
        pq.push(newNode);
    }

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        Node* newNode = new Node(left, right);
        pq.push(newNode);
    }

    if (pq.empty()) {
        return frequencies;
    }

    Node* root = pq.top();

    generateCodes(root, "", codes);

    delete root;

    return frequencies;
}

int main() {
    string text;
    getline(in, text);

    map<char, string> codes;
    map<char, int> frequencies = huffmanEncoding(text, codes);

    out<< codes.size() << "\n";
    for (const auto& pair : codes) {
        out << pair.first << " " << frequencies[pair.first] << "\n";
    }

    for (char ch : text) {
        out << codes[ch];
    }


    return 0;
}