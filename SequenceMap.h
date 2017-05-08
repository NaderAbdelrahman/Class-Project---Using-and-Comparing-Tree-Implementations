#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

class SequenceMap {

 public:
  // Zero-parameter constructor
  SequenceMap() = default;
  // Copy-Constructor
  SequenceMap(const SequenceMap &rhs) = default;
  // Copy-Assignment
  SequenceMap& operator=(const SequenceMap &rhs) = default;
  // Move-Constructor
  SequenceMap(SequenceMap &&rhs) = default;
  // Move-Assignment
  SequenceMap& operator=(SequenceMap &&rhs) = default;
  // Destructor
  ~SequenceMap() = default;
  // End of Big-Five

  // Two Parameter Constructor
  SequenceMap(const std::string &a_rec_seq, const std::string &an_enz_acro) {
   recognition_sequence_ = a_rec_seq;
   enzyme_acronyms_.push_back(an_enz_acro);
  }
  bool operator<(const SequenceMap &rhs) const{
   return recognition_sequence_ < rhs.recognition_sequence_;
  }
  friend std::ostream &operator<<(std::ostream &out, const SequenceMap &seq_map) {
   for(unsigned int i = 0; i < seq_map.enzyme_acronyms_.size(); ++i){
    out << seq_map.enzyme_acronyms_[i] << " ";
   }
   out << endl;
   // out << seq_map.recognition_sequence_ << endl;
   return out;
 }
 void Merge(const SequenceMap &other_sequence){
  // unsigned int size = enzyme_acronyms_.size();
  // enzyme_acronyms_.insert(enzym_acronyms_.end(), other_sequence.first(), 
  //       other_sequence.end());
  for(unsigned int i = 0; i < other_sequence.enzyme_acronyms_.size(); ++i){
   enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_.at(i));
  }
 }
  // int total_rec_calls_getter(){return total_rec_calls;}
  // void total_rec_calls_adder(){
  //   ++total_rec_calls_;
  // }
 private:
 std::string  recognition_sequence_;
 vector<string>  enzyme_acronyms_;
};


#endif //SEQUENCE_MAP_H