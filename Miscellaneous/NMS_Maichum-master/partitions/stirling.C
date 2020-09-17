#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

int main(int argc, const char *const *argv)
{
  // optional argument specifies max p in S(p,k)
  unsigned max_p = 10;
  if (argc >= 2) {
    std::stringstream stream; stream << argv[1];
    stream >> max_p;
  }

  std::vector<std::vector<unsigned> > S(max_p+1);
  S[0].resize(2);
  S[0][0] = 1;

  for (unsigned p = 1; p <= max_p; ++p) {
    S[p].resize(p+2);
    for (unsigned k = 1; k <= p; ++k)
      S[p][k] = S[p-1][k-1] + k*S[p-1][k];
  }

  for (std::vector<std::vector<unsigned> >::const_iterator
         it = S.begin(); it != S.end(); ++it) {
    std::copy(it->begin(), it->end()-1,
              std::ostream_iterator<unsigned>(std::cout, " "));

    std::cout << '\n';
  }
}
