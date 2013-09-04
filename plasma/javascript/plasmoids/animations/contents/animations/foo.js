//*************************************************************************//
function FooAnimation(target, duration) {
    this.target = target;
    this.duration = duration;

    this.updateCurrentTime = function(currentTime) {
        var delta = currentTime/this.duration;
        this.target.scale = delta;
    }
}

registerAnimation("Foo", FooAnimation)

