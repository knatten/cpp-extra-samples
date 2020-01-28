/*
This example shows how to acquire HDR images from the Zivid camera in a loop
(while actively changing some HDR settings).
*/

#include <Zivid/Zivid.h>

#include <iostream>

int main()
{
    try
    {
        Zivid::Application zivid;

        std::cout << "Connecting to the camera" << std::endl;
        auto camera = zivid.connectCamera();

        std::cout << "Configuring the camera settings" << std::endl;
        std::vector<std::vector<Zivid::Settings>> settingsHDRVector;

        Zivid::Settings settings;
        settings.set(Zivid::Settings::Brightness{ 1 })
            .set(Zivid::Settings::Gain{ 1 })
            .set(Zivid::Settings::Bidirectional{ false })
            .set(Zivid::Settings::Filters::Contrast::Enabled::yes)
            .set(Zivid::Settings::Filters::Contrast::Threshold{ 5 })
            .set(Zivid::Settings::Filters::Gaussian::Enabled::yes)
            .set(Zivid::Settings::Filters::Gaussian::Sigma{ 1.5 })
            .set(Zivid::Settings::Filters::Outlier::Enabled::yes)
            .set(Zivid::Settings::Filters::Outlier::Threshold{ 5 })
            .set(Zivid::Settings::Filters::Reflection::Enabled::yes)
            .set(Zivid::Settings::Filters::Saturated::Enabled::yes)
            .set(Zivid::Settings::BlueBalance{ 1.081 })
            .set(Zivid::Settings::RedBalance{ 1.709 });

        std::vector<size_t> iris{ 10U, 20U, 30U };
        std::vector<std::vector<int>> exposureTimeFrames{ { 10000, 90000, 40000 },
                                                          { 40000, 10000, 90000 },
                                                          { 90000, 40000, 10000 } };

        for(size_t i = 0; i < 3; ++i)
        {
            std::vector<Zivid::Settings> settingsHDR;
            for(size_t j = 0; j < 3; ++j)
            {
                settingsHDR.push_back(
                    settings.set(Zivid::Settings::Iris{ iris[j] })
                        .set(Zivid::Settings::ExposureTime{ std::chrono::microseconds{ exposureTimeFrames[i][j] } }));
            }
            settingsHDRVector.push_back(settingsHDR);
            const auto hdrFrame = Zivid::HDR::capture(camera, settingsHDRVector[i]);
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << "Error: " << Zivid::toString(e) << std::endl;
        return EXIT_FAILURE;
    }
}