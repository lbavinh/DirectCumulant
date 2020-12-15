#include "PicoDstVersion.h"

#include <iostream>
#include <string>

int main(int argc, char **argv)
{
  bool isVersion=false, isBin=false, isSrc=false, isInc=false;
  std::string strBin=TOSTRING(PICO_DST_BIN_DIR);
  std::string strSrc=TOSTRING(PICO_DST_SRC_DIR);
  std::string strInc=TOSTRING(PICO_DST_INC_DIR);
  std::string strVersion_tag=TOSTRING(GIT_TAG_VERSION);
  std::string strVersion_branch=TOSTRING(GIT_BRANCH);
  std::string strVersion_hash=TOSTRING(GIT_COMMIT_HASH);
  std::string strVersion=strVersion_tag+"."+strVersion_branch+"-"+strVersion_hash;
  std::string strOutput="";
  if (argc<2)
  {
    std::cerr << "Usage: PicoDst-config [--bindir] [--srcdir] [--incdir] [--version]" << std::endl;
    return 1;
  }

  for (int i = 1; i < argc; i++)
  {
    if (std::string(argv[i]) != "--version" &&
      std::string(argv[i]) != "--bindir" &&
      std::string(argv[i]) != "--srcdir" &&
      std::string(argv[i]) != "--incdir")
    {
            std::cerr << "\n[ERROR]: Unknown parameter " << i << ": " << argv[i] << std::endl;
      return 1;
    }
    else
    {
      if (std::string(argv[i]) == "--version")
      {
        isVersion = true;
        continue;
      }
      if (std::string(argv[i]) == "--bindir")
      {
        isBin = true;
        continue;
      }
      if (std::string(argv[i]) == "--incdir")
      {
        isInc = true;
        continue;
      }
      if (std::string(argv[i]) == "--srcdir")
      {
        isSrc = true;
        continue;
      }
    }
  }

  if (isVersion) strOutput+=(strVersion+" ");
  if (isBin) strOutput+=(strBin+" ");
  if (isInc) strOutput+=(strInc+" ");
  if (isSrc) strOutput+=(strSrc+" ");

  std::cout << strOutput << std::endl;

  return 0;
}
