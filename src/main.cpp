#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

 #define MOTOR_BACK_LEFT 20
 #define MOTOR_BACK_RIGHT 11
 #define MOTOR_FRONT_LEFT 17
 #define MOTOR_FRONT_RIGHT 14
 #define INTAKE_RIGHT 19
 #define INTAKE_LEFT 15
 #define LIFT_LEFT 18
 #define LIFT_RIGHT 13

void opcontrol() {
	using namespace pros;

	int left, right;
	bool iForward, iReverse;
	bool liftDown, liftUp;

	Motor driveBackLeft(MOTOR_BACK_LEFT, true);
	Motor driveBackRight(MOTOR_BACK_RIGHT);
	Motor driveFrontLeft(MOTOR_FRONT_LEFT, true);
	Motor driveFrontRight(MOTOR_FRONT_RIGHT);
	Motor intakeRight(INTAKE_RIGHT);
	Motor intakeLeft(INTAKE_LEFT, true);
	Motor liftLeft(LIFT_LEFT);
	Motor liftRight(LIFT_RIGHT, true);

	Controller joystick(CONTROLLER_MASTER);

	while (true) {
		left = joystick.get_analog(ANALOG_LEFT_Y);
	  right = joystick.get_analog(ANALOG_RIGHT_Y);

		iForward = joystick.get_digital(DIGITAL_R1);
		iReverse = joystick.get_digital(DIGITAL_R2);

		liftDown = joystick.get_digital(DIGITAL_L2);
		liftUp = joystick.get_digital(DIGITAL_L1);

		driveBackLeft = right;
		driveFrontLeft = right;
		driveBackRight = left;
		driveFrontRight = left;

		if (iForward) {
			intakeLeft = 127;
			intakeRight = 127;
		}
		else if (iReverse) {
			intakeLeft = -80;
			intakeRight = -80;
		}
		else {
			intakeLeft = 0;
			intakeRight = 0;
		}

		if (liftUp) {
			liftRight = 127;
			liftLeft = 127;
		}
		else if (liftDown) {
			liftRight = -127;
			liftLeft = -127;
		}
		else {
			liftRight = 0;
			liftLeft = 0;
			liftRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			liftLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		}

		delay(20); //20 milliseconds.. helps cool CPU

	}
}
