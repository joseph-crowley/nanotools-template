#include "TFile.h"
#include "TH1F.h"
#include "TDirectory.h"
#include "TKey.h"
#include "TList.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TText.h"
#include <fstream>
#include <unordered_map>

std::unordered_map<std::string, double> integrateHistograms(const char* filename)
{
   TFile* file = TFile::Open(filename);
   if (!file || file->IsZombie()) {
      std::cerr << "Error: Could not open file " << filename << std::endl;
      return std::unordered_map<std::string, double>();
   }

    std::string filename_str(filename);
    std::size_t last_slash_index = filename_str.find_last_of('/');
    if (last_slash_index != std::string::npos) {
        filename_str = filename_str.substr(last_slash_index + 1);
    }
   std::string outfile_name = "integral_report_" + filename_str + ".txt";

   std::ofstream outfile(outfile_name);

   std::unordered_map<std::string, double> integrals;
   TIter next(file->GetListOfKeys());
   TKey* key;
   while ((key = (TKey*)next())) {
      TH1F* hist = (TH1F*)key->ReadObj();
      double integral = hist->Integral();
      integrals[hist->GetName()] = integral;
      outfile << hist->GetName() << "\t" << integral << std::endl;
   }

   outfile.close();
   file->Close();

   return integrals;
}

