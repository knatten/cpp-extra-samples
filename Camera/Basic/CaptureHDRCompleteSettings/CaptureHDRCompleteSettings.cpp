/*
This example shows how to acquire an HDR image from the Zivid camera with fully
configured settings for each frame. In general, taking an HDR image is a lot
simpler than this as the default settings work for most scenes. The purpose of
this example is to demonstrate how to configure all the settings.
*/

#include <Zivid/CloudVisualizer.h>
#include <Zivid/Zivid.h>

#include <iostream>

int main()
{
    try
    {
        Zivid::Application zivid;

        std::cout << "Setting up visualization" << std::endl;
        Zivid::CloudVisualizer vis;
        zivid.setDefaultComputeDevice(vis.computeDevice());

        std::cout << "Connecting to the camera" << std::endl;
        auto camera = zivid.connectCamera();

        std::cout << "Configuring settings same for all HDR frames" << std::endl;
        auto settingsDefault = Zivid::Settings();
        settingsDefault.set(Zivid::Settings::Brightness{ 1 })
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

        std::cout << "Configuring settings different for all HDR frames" << std::endl;
        size_t iris[3] = { 10U, 20U, 30U };
        int exposureTime[3] = { 10000, 20000, 30000 };
        std::vector<Zivid::Settings> settingsHDR;
        for(size_t i = 0; i < 3; ++i)
        {
            settingsHDR.push_back(
                settingsDefault.set(Zivid::Settings::Iris{ iris[i] })
                    .set(Zivid::Settings::ExposureTime{ std::chrono::microseconds{ exposureTime[i] } }));
            std::cout << "Frame " << i << " " << settingsHDR[i] << std::endl;
        }

        std::cout << "Capturing HDR frame" << std::endl;
        const auto hdrFrame = Zivid::HDR::capture(camera, settingsHDR);

        std::cout << "Saving the frame" << std::endl;
        hdrFrame.save("HDR.zdf");

        std::cout << "Displaying the frame" << std::endl;
        vis.showMaximized();
        vis.show(hdrFrame);
        vis.resetToFit();

        std::cout << "Running the visualizer. Blocking until the window closes" << std::endl;
        vis.run();
    }
    catch(const std::exception &e)
    {
        std::cerr << "Error: " << Zivid::toString(e) << std::endl;
        return EXIT_FAILURE;
    }
}