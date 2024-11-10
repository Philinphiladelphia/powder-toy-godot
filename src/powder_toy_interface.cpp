// Include the header file
#include "powder_toy_interface.h"

#include <deque>  // Include deque for circular buffer
#include <chrono>  // Include for high_resolution_clock

// Powder Toy Imports
#include "SimulationConfig.h"
#include "simulation/ElementCommon.h"
#include "common/platform/Platform.h"

using std::placeholders::_1;

// Goal: have a node in godot that is a powder toy simulation.

PowderToyInterface::PowderToyInterface()
{
    InitializeSingletons();
}

void PowderToyInterface::RunSimFrame() {
    explicit_singletons_->simulation->BeforeSim();
    explicit_singletons_->simulation->UpdateParticles(0, YRES * XRES);
    explicit_singletons_->simulation->AfterSim();
}

void PowderToyInterface::InitializeSingletons()
{
    explicit_singletons_ = std::make_unique<ExplicitSingletons>();

	Platform::SetupCrt();

	// This directory should at least have powder.pref in it
	std::string gameDir = "/home/phil/.local/share/The Powder Toy/";

	if (Platform::ChangeDir(gameDir))
	{
		Platform::sharedCwd = Platform::GetCwd();
	}
	else
	{
		perror("failed to chdir to requested ddir");
	}

	// Initialize the global preferences
	explicit_singletons_->globalPrefs = std::make_unique<GlobalPrefs>();

	// init the http request manager
	// I don't know if I'm going to use http, but it's easier to init it than rip it out.
	ByteString proxyString = "";
	ByteString cafileString = "";
	ByteString capathString = "";
	bool disableNetwork = true;
	explicit_singletons_->requestManager = http::RequestManager::Create(proxyString, cafileString, capathString, disableNetwork);

	explicit_singletons_->client = std::make_unique<Client>();
	Client::Ref().Initialize();

	// Initialize the save renderer
	explicit_singletons_->saveRenderer = std::make_unique<SaveRenderer>();
	explicit_singletons_->favorite = std::make_unique<Favorite>();

	// Initialize the UI engine
	explicit_singletons_->engine = std::make_unique<ui::Engine>();

	WindowFrameOps windowFrameOps{
		1, // Scale
		true, // Resizable
		false, // Fullscreen
		false, // AltFullscreen
		true, // ForceIntegerScaling
		false, // BlurryScaling
	};

	// set defaults
	auto &engine = ui::Engine::Ref();

	// Initialize the simulation data
    explicit_singletons_->simulation = std::make_unique<Simulation>();
	explicit_singletons_->simulationData = std::make_unique<SimulationData>();
	//engine.ShowWindow(gameController->GetView());
}

void PowderToyInterface::SetSimFramerate(int framerate)
{
    auto &engine = ui::Engine::Ref();
    FpsLimitExplicit limit;
    limit.value = framerate;
    engine.SetFpsLimit(limit);
}

void PowderToyInterface::SetSimDrawingFrequency(int frequency)
{
    auto &engine = ui::Engine::Ref();
    engine.SetDrawingFrequencyLimit(frequency);
}

// point, circle, triangle, polygon, line, arc
void PowderToyInterface::MakeCircle(PowderCircle &circle) {
    printf("Creating point at (%d, %d) with radius %d and element %d\n", circle.x, circle.y, circle.r, circle.element);
    explicit_singletons_->simulation->create_part(-1, circle.x, circle.y, circle.element, 0);

	// time to create via brush. Should probably figure that syntax out
}

void PowderToyInterface::GetParticles(int* particles) {
    // Ensure the particles field is properly initialized
    static_assert(YRES * XRES == 40000, "The size of the particles array must be 40000.");

    // Copy pmap to sim_data.particles
    for (int i = 0; i < YRES; ++i) {
        for (int j = 0; j < XRES; ++j) {
            particles[i * XRES + j] = explicit_singletons_->simulation->pmap[i][j];
            printf("Particle at (%d, %d) is %d\n", i, j, explicit_singletons_->simulation->pmap[i][j]);
        }
    }
}

// next testing step is copy from one sim to another

// void PowderToyInterface::GetForceVectors() {
//     // Copy vx, vy, pv, and hv to sim_data.force_data
//     for (int i = 0; i < YCELLS; ++i) {
//         std::copy(&sim_->vx[i][0], &sim_->vx[i][0] + XCELLS, sim_data.force_data.vx.begin() + i * XCELLS);
//         std::copy(&sim_->vy[i][0], &sim_->vy[i][0] + XCELLS, sim_data.force_data.vy.begin() + i * XCELLS);
//         std::copy(&sim_->pv[i][0], &sim_->pv[i][0] + XCELLS, sim_data.force_data.pv.begin() + i * XCELLS);
//         std::copy(&sim_->hv[i][0], &sim_->hv[i][0] + XCELLS, sim_data.force_data.hv.begin() + i * XCELLS);
//     }
// }

// void PowderToyInterface::SetForceVectors() {
//     // Ensure the size of the force vectors arrays matches the size of vx, vy, pv, and hv
//     if (sim_data.force_data.vx.size() != YCELLS * XCELLS ||
//         sim_data.force_data.vy.size() != YCELLS * XCELLS ||
//         sim_data.force_data.pv.size() != YCELLS * XCELLS ||
//         sim_data.force_data.hv.size() != YCELLS * XCELLS) {
//         throw std::runtime_error("Size of force vectors in SimData does not match the expected size.");
//     }

//     // Copy vx, vy, pv, and hv from sim_data.force_data to the simulation
//     for (int i = 0; i < YCELLS; ++i) {
//         std::copy(sim_data.force_data.vx.begin() + i * XCELLS, sim_data.force_data.vx.begin() + (i + 1) * XCELLS, std::begin(sim_->vx[i]));
//         std::copy(sim_data.force_data.vy.begin() + i * XCELLS, sim_data.force_data.vy.begin() + (i + 1) * XCELLS, std::begin(sim_->vy[i]));
//         std::copy(sim_data.force_data.pv.begin() + i * XCELLS, sim_data.force_data.pv.begin() + (i + 1) * XCELLS, std::begin(sim_->pv[i]));
//         std::copy(sim_data.force_data.hv.begin() + i * XCELLS, sim_data.force_data.hv.begin() + (i + 1) * XCELLS, std::begin(sim_->hv[i]));
//     }
// }