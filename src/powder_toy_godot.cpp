#include "powder_toy_godot.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void PowderToy::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_powder_state"), &PowderToy::GetParticles);
    ClassDB::bind_method(D_METHOD("draw_powder_circle"), &PowderToy::DrawCircle);
    ClassDB::bind_method(D_METHOD("process_powder_frame"), &PowderToy::ProcessPowderFrame);
}

Array PowderToy::GetParticles() const {
    Array arr;

    // Assuming XRES and YRES are defined somewhere in your code
    arr.resize(YRES);

    int parts_array[XRES * YRES];
    powder_toy_interface->GetParticles(parts_array);

    for (int y = 0; y < YRES; y++) {
        Array row;
        row.resize(XRES);
        for (int x = 0; x < XRES; x++) {
            row[x] = Variant(parts_array[y * XRES + x]);
        }
        arr[y] = row;
    }

    return arr;
}

void PowderToy::DrawCircle(int x, int y, int r, int element) const {
    PowderCircle circle;
    circle.x = 0;
    circle.y = 0;
    circle.r = 20;
    circle.element = 49;
    powder_toy_interface->MakeCircle(circle);
}

PowderToy::PowderToy() {
	// Initialize any variables here.
	time_passed = 0.0;

    powder_toy_interface = std::make_shared<PowderToyInterface>();
    // powder_toy_interface->SetSimFramerate(300);
    // powder_toy_interface->SetSimDrawingFrequency(30);
}

PowderToy::~PowderToy() {
	// Add your cleanup here.
}

void PowderToy::ProcessPowderFrame() {
    powder_toy_interface->RunSimFrame();
}


// works! Edit it, rebuild with scons, and it goes straight into the game.
void PowderToy::_process(double delta) {
	time_passed += delta*10;

	Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 1.5)));

	set_position(new_position);
}