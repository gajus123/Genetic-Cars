#include "WorldWidget.h"

WorldWidget::WorldWidget(QWidget *parent, Qt::WindowFlags flags) : QWidget(parent, flags), timerId_(0) {
	b2Vec2 gravity(GRAVITY_X, GRAVITY_Y);
	world_ = new b2World(gravity);
	
	for (unsigned int i = 0; i < NUMBER_OF_BALLS; ++i) {
		int dx = BALLS_MAX_DISTANCE_X/2 - qrand() % BALLS_MAX_DISTANCE_X;
		int dy = qrand() % BALLS_MAX_DISTANCE_Y;
		balls_.append(createBall(b2Vec2(BALLS_MAX_DISTANCE_X+dx, BALL_STARTING_Y-dy), BALL_RADIUS));
	}
	
	transform_.scale(SCALE_X, SCALE_Y);
	transform_.translate(TRANSLATE_X, TRANSLATE_Y);
}
void WorldWidget::paintEvent(QPaintEvent *event) {
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, true);
	p.setTransform(transform_);
	foreach(const Ball& o, balls_) {
		drawEllipse(p, o);
	}
}
WorldWidget::Ball WorldWidget::createBall(const b2Vec2& pos, float32 radius) {
	Ball ball;
	
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position = pos;
	ball.body_ = world_->CreateBody(&bd);
	
	b2CircleShape shape;
	shape.m_radius = radius;
	
	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = BALL_DENSITY;
	fd.friction = BALL_FRICTION;
	fd.restitution = BALL_RESTITUATION;
	ball.fixture_ = ball.body_->CreateFixture(&fd);
	return ball;
}
void WorldWidget::drawEllipse(QPainter &p, const Ball& ball) {
	float32 x = ball.body_->GetPosition().x;
	float32 y = ball.body_->GetPosition().y;
	float32 r = ball.fixture_->GetShape()->m_radius;
	p.drawEllipse(QPointF(x, y), r, r);
}
void WorldWidget::timerEvent(QTimerEvent *event) {
	if(event->timerId() == timerId_) {
		world_->Step(WORLD_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
		update();
	}
}
void WorldWidget::start() {
	if(!timerId_) {
		timerId_ = startTimer(FRAME_TIME);
	}
}
WorldWidget::~WorldWidget() {
	delete world_;
}