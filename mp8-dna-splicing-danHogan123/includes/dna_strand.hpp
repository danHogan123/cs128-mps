#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const char* dna);

// helpers
  unsigned int SizeOf(const char* pattern);
  unsigned int SizeOf(DNAstrand& to_splice_in);
  bool Verify(const char* pattern, unsigned int current);
  void WriteIt(const DNAstrand& dna);
  void FillEnd(unsigned int& current_idx, Node*& end, unsigned int size_pattern);
  unsigned int Occurances(const char* pattern);
  void FindIndex(const char* pattern, Node*& curr, unsigned int& current_idx);
  
  void FromHead(const char* pattern, Node*& curr);
  void FromTail(const char* pattern, Node*& curr);
  void FromMiddle(const char* pattern, Node*& curr);

  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();

  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif