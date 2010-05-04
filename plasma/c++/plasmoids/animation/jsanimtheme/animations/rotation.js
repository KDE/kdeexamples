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

registerAnimation("rotation.js", RotationAnimation)

