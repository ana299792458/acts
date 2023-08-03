#include <vector>
#include <string>
#include <vector>
#include <string>
#include <iostream> // for std::cout
#include "TFile.h"
#include "TEfficiency.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TColor.h"


void plotHist(const std::vector<std::string>& fileNames,
                    const std::vector<std::string>& treeBranches,
                    const std::vector<std::string>& labels
                    //double yMin = 0.0, double yMax = 1.0,
                    //double xMin = -4.0, double xMax = 4.0
                    //,const std::string& title
)
                    
{
    // Check that the number of files, branches, and labels match
    if (fileNames.size() != treeBranches.size() || fileNames.size() != labels.size())
    {
        std::cout << "Error: Number of files, branches, and labels do not match!" << std::endl;
        return;
    }

    // Define marker colors
    std::vector<Color_t> markerColors = {kBlack, kBlue, kRed, kGreen, kOrange, kMagenta, kCyan};
    std::vector<Color_t> markerStyles = {20, 21, 22, 29, 20, 21, 22};

    // Create a canvas
    TCanvas* c1 = new TCanvas("c1", "Histograms", 800, 600);

    TLegend* legend = new TLegend(0.4,0.15,0.7,0.3); // or position (x1,y1,x2,y2) in the range [0,1]

    // Loop over the root files and plot histograms
    for (size_t i = 0; i < fileNames.size(); ++i)
    {
        // Open the ROOT file
        TFile* file = TFile::Open(fileNames[i].c_str());
        if (!file || file->IsZombie())
        {
            std::cout << "Error: Failed to open file: " << fileNames[i] << std::endl;
            continue;
        }

        // Get the histogram from the file
        TEfficiency* hist = (TEfficiency*)file->Get(treeBranches[i].c_str());
        if (!hist)
        {
            std::cout << "Error: Failed to retrieve histogram from file: " << fileNames[i] << std::endl;
            file->Close();
            continue;
        }

        // Set marker color for this histogram
        int markerColor = markerColors[i % markerColors.size()]; // Use modulo to repeat colors if needed
        hist->SetMarkerColor(markerColor);
        hist->SetLineColor(markerColor);
        //hist->SetMarkerStyle(20 + i);
        hist->SetMarkerSize(0.5);

        int markerStyle = markerStyles[i % markerStyles.size()];
        hist->SetMarkerStyle(markerStyle);

        // Draw the histogram with points (markers) on the same canvas
        if (i == 0)
            hist->Draw("AP"); // "A" to draw axis, "P" to draw markers
        else
            hist->Draw("P SAME"); // "SAME" to draw on the same canvas

        // Add entry to the legend
        legend->AddEntry(hist, labels[i].c_str(), "lep"); // "lep" is the marker option (point with error bars)

        // Close the file
        file->Close();
    }

    // Draw the legend
    legend->SetTextSize(0.03);
    legend->Draw();

    // Set axis labels and title (you can customize these as needed)
    // hist->GetXaxis()->SetTitle("#eta");
    // hist->GetYaxis()->SetTitle("Efficiency");
    // hist->SetTitle("Track Efficiency vs #eta");

    // Update the canvas
    c1->Update();
};


