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

registerAnimation("fade.js", FadeAnimation)

