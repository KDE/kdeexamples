function ZoomAnimation(target, duration) {
    this.target = target;
    this.duration = duration;

    this.updateCurrentTime = function(currentTime) {

	var delta = currentTime/this.duration;
	this.target.scale = delta;

    }
}

registerAnimation("zoom.js", ZoomAnimation)
