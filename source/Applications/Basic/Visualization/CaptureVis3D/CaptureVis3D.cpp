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

        std::cout << "Connecting to camera" << std::endl;
        auto camera = zivid.connectCamera();

        std::cout << "Adjusting the iris" << std::endl;
        camera << Zivid::Settings::Iris{ 20 };

        std::cout << "Capture a frame" << std::endl;
        auto frame = camera.capture();

        std::cout << "Display the frame" << std::endl;
        vis.showMaximized();
        vis.show(frame);
        vis.resetToFit();

        std::cout << "Run the visualizer. Block until window closes" << std::endl;
        vis.run();
    }
    catch(const std::exception &e)
    {
        std::cerr << "Error: " << Zivid::toString(e) << std::endl;
        return EXIT_FAILURE;
    }
}