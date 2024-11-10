extends PowderToy

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	draw_powder_circle(100, 100, 20, 49)
		# Right now, I'm correctly printing out a billion zeros which are in the pmap. 
		# I need to make the create part function work.
	
	print()
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	process_powder_frame()
	pass
