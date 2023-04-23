#pragma once

#include "byte_stream.hh"

#include <string>
#include <list>
using namespace std;

class IdxData {
public:
  uint64_t idx;
  string data;
  uint64_t right() const;
};
inline bool operator< (const IdxData& lhs, const IdxData& rhs);
class Reassembler
{
private:
  list<IdxData> buffer_;
  uint64_t next_byte_{0};
  uint64_t bytes_pending_{0};
  void push_and_tidy_list(uint64_t idx, string data, const Writer& output);
  void try_merge(list<IdxData>::iterator it, list<IdxData>::const_iterator end);
  uint64_t calc_buffer();
public:
  /*
   * Insert a new substring to be reassembled into a ByteStream.
   *   `first_index`: the index of the first byte of the substring
   *   `data`: the substring itself
   *   `is_last_substring`: this substring represents the end of the stream
   *   `output`: a mutable reference to the Writer
   *
   * The Reassembler's job is to reassemble the indexed substrings (possibly out-of-order
   * and possibly overlapping) back into the original ByteStream. As soon as the Reassembler
   * learns the next byte in the stream, it should write it to the output.
   *
   * If the Reassembler learns about bytes that fit within the stream's available capacity
   * but can't yet be written (because earlier bytes remain unknown), it should store them
   * internally until the gaps are filled in.
   *
   * The Reassembler should discard any bytes that lie beyond the stream's available capacity
   * (i.e., bytes that couldn't be written even if earlier gaps get filled in).
   *
   * The Reassembler should close the stream after writing the last byte.
   */
  void insert( uint64_t first_index, std::string data, bool is_last_substring, Writer& output );

  // How many bytes are stored in the Reassembler itself?
  uint64_t bytes_pending() const;
};
