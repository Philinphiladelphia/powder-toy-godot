#ifndef GDPOWDER_TOY_H
#define GDPOWDER_TOY_H

#include <godot_cpp/classes/sprite2d.hpp>
#include "powder_toy_interface.h"

namespace godot {

class PowderToy : public Sprite2D {
	GDCLASS(PowderToy, Sprite2D)

private:
	double time_passed;
    std::shared_ptr<PowderToyInterface> powder_toy_interface;

protected:
	static void _bind_methods();

public:
	PowderToy();
	~PowderToy();
	void Run();
    Array GetParticles() const;
    void DrawCircle(int x, int y, int r, int element) const;
	void ProcessPowderFrame();

	void _process(double delta) override;
};

}

#endif