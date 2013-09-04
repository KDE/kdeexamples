//*************************************************************************//
function ZoomAnimation(target, duration) {
    this.target = target;
    this.duration = duration;

    this.updateCurrentTime = function(currentTime) {

	var delta = currentTime/this.duration;
	this.target.scale = delta;

    }
}

registerAnimation("ZoomAnimation", ZoomAnimation)

//*************************************************************************//
function RotationAnimation(target, duration) {
    this.target = target;
    this.duration = duration;
    this.angle = 360;
    //TODO: allow to set angle and axis on the 'constructor'
    //this.axis = axis;

    this.updateCurrentTime = function(currentTime) {

	var delta = currentTime/this.duration;
	this.target.rotation = delta * this.angle;

    }
}

registerAnimation("RotationAnimation", RotationAnimation)

//*************************************************************************//
function FadeAnimation(target, duration) {
    this.target = target;
    this.duration = duration;
    //TODO: maybe a 'resetAnimation' function could use this
    //and be called when the animation status change from running
    //to stopped
    this.opacityStart = target.opacity

    this.updateCurrentTime = function(currentTime) {

	var delta = currentTime/duration;
	target.opacity = delta;

    }
}

registerAnimation("FadeAnimation", FadeAnimation)

//*************************************************************************//
function SlideAnimation(target, duration) {
    this.target = target;
    this.duration = duration;
    this.x = target.x

    this.updateCurrentTime = function(currentTime) {

	var delta = currentTime/this.duration;
	this.target.x = delta * this.x;

    }
}

registerAnimation("SlideAnimation", SlideAnimation)


