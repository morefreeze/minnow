Checkpoint 0 Writeup
====================

My name: [your name here]

My SUNet ID: [your sunetid here]

I collaborated with: [list sunetids here]

I would like to credit/thank these classmates for their help: [list sunetids here]

This lab took me about 2 hours to do. I did not attend the lab session.

My secret code from section 2.1 was: [code here]

- Optional: I had unexpected difficulty with:
I added char* buffer_ to implement ring array, but I met memory leak when call peek(),
I know I should copy or move buffer_ correctly and carefully. So I implement four ctor
and dtor and write many likely code which copy or move member fields.
I met another question is generate and return correct string_view when call peek().
why peek is so difficulty? I need combine two sections of buffer_ and pass them to string_view.
But I can't define a string in peek function, because it will be released
after finish func, so that AddressSanitizer: stack-use-after-return on address.
So I need define member string and build it in each peek().
In consider of efficacy, I use memcpy but string.data() return const char*,
I need use const_cast to remove const qualifier. I pass all tests when I finish it.

- Optional: I think you could make this lab better by: [describe]

- Optional: I was surprised by: [describe]

- Optional: I'm not sure about: [describe]
