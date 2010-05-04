function SlideAnimation(target, duration) {
    this.target = target;
    this.duration = duration;
    this.x = target.x

    this.updateCurrentTime = function(currentTime) {

	var delta = currentTime/this.duration;
	this.target.x = delta * this.x;

    }
}

registerAnimation("slide.js", SlideAnimation)

