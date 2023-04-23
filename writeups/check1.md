Checkpoint 1 Writeup
====================

My name: [your name here]

My SUNet ID: [your sunetid here]

I collaborated with: [list sunetids here]

I would like to thank/reward these classmates for their help: [list sunetids here]

This lab took me about 3.5 hours to do. I [did/did not] attend the lab session.

reassembler will reassemble all substrings which are received from somewhere by order.
you can debug with like `gdb build/tests/byte_stream_one_write`.
The benchmark should greater than 0.1Gb/s and 10Gb/s is the best.

Program Structure and Design of the Reassembler:
Reassembler should push next byte to Writer ASAP, should store substring which fit in capacity,
should discard any bytes that lie out of capacity.
It should also close stream when the last substring is finish.

Implementation Challenges:
how can i figure out output.capacity? Reassembler store buffer only save at least
campacity bytes, but how to know that? pass output of insert.
push_and_tidy_list push data to buffer_ list and use try_merge
to tidy whole linked list, try_merge will try to merge continuous item into one
as its description.

Remaining Bugs:
[]

- Optional: I had unexpected difficulty with:
I struggle with vscode debug, I tried google but failed debug in cmake.
but i write my_debug to start lldb in command line, it's brute but it works.

- Optional: I think you could make this lab better by: [describe]

- Optional: I was surprised by: [describe]

- Optional: I'm not sure about: [describe]
