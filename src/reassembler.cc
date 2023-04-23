#include "reassembler.hh"

using namespace std;

bool operator< (const IdxData& lhs, const IdxData& rhs) {
  if (lhs.idx == rhs.idx) {
    return lhs.data.size() > rhs.data.size();
  }
  return lhs.idx < rhs.idx;
}

uint64_t IdxData::right() const {
  return idx + data.size();
}

void Reassembler::push_and_tidy_list(uint64_t idx, string data, const Writer& output) {
  auto output_right(output.bytes_pushed() + output.available_capacity());
  // scenario 3: idx+data.size() out of output capacity, discard it
  if (idx >= output_right) {
    return;
  }
  IdxData item({idx, move(data)});
  if (output_right < item.right()) {
    item.data = item.data.substr(0, output_right - idx);
  }
  auto it = lower_bound(buffer_.begin(), buffer_.end(), item);
  buffer_.emplace(it, item);
  try_merge(it, buffer_.end());
  calc_buffer();
}

// try_merge try to merge overlapping IdxData to make sure each adjacent IdxData has at least 0 byte gap
void Reassembler::try_merge(list<IdxData>::iterator it, list<IdxData>::const_iterator end) {
  if (it == end) {
    return;
  }
  auto next(it);
  next++;
  while (next != end) {
    if (next->idx <= it->right() && next->right() < it->right()) {
      // scenario 1: it cross next  |it->idx    <next->idx   |it->right    >next->right
      // concat next substring to it and remove next
      it->data += next->data.substr(it->right()-it->idx, next->right() - it->right());
      buffer_.erase(next);
    } else if (next->right() <= it->right()) {
      // scenario 2: it cover next completely |it->idx     <next->idx  >next->right    |it->right
      // just remove next
      buffer_.erase(next);
    } else {
      it++;
      next++;
    }
  }
}

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring, Writer& output )
{
  // Your code here.
  if (is_last_substring) {
    output.close();
  }
  if (data.size() == 0) {
    return;
  }
  push_and_tidy_list(first_index, move(data), output);
  while (!buffer_.empty()) {
    auto head(buffer_.front());
    if (head.idx > next_byte_) {
      break;
    }
    if (head.right() > next_byte_) {
      auto new_data(head.data.substr(head.data.size() - (head.right() - next_byte_)));
      output.push(move(new_data));
      next_byte_ = output.bytes_pushed();
    }
    buffer_.pop_front();
  }
  calc_buffer();
}

uint64_t Reassembler::calc_buffer() {
  bytes_pending_ = 0;
  for (auto it = buffer_.begin(); it != buffer_.end(); ++it) {
    bytes_pending_ += it->data.size();
  }
  return bytes_pending_;
}

uint64_t Reassembler::bytes_pending() const
{
  return bytes_pending_;
}
