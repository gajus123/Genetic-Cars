#include "WorldWidget.h"

WorldWidget::WorldWidget(QWidget *parent, Qt::WindowFlags flags) : QWidget(parent, flags), timerId_(0) {
	b2Vec2 gravity(0.0f, -10.0f);
	world_ = new b2World(gravity);
	
	for (unsigned int i = 0; i < 30; ++i) {
		int dx = 18 - qrand() % 36;
		int dy = qrand() % 2;
		balls_.append(createBall(b2Vec2(18.0f+dx, 62.0f-dy), 1.0f));
	}
	
	transform_.scale(10.0f, -10.0f);
	transform_.translate(0.0f, -64.0f);
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
	fd.density = 1.0f;
	fd.friction = 1.0f;
	fd.restitution = 0.6f;
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
		world_->Step(1.0f/60.0f, 8, 3);
		update();
	}
}
void WorldWidget::start() {
	std::cout << "Start\n";
	if(!timerId_) {
		timerId_ = startTimer(1000/60);
	}
}
WorldWidget::~WorldWidget() {
	delete world_;
}