//
// \author Rafa� Galczak
// \date 14.01.18
//

#include "include/Genotype.h"

namespace Algorithm {

	Genotype::Genotype() :
			rng_(rd_()),
			front_radius_(randFloat(0.0f, MAX_RADIUS_LIMIT), 0.0f, MAX_RADIUS_LIMIT),
			back_radius_(randFloat(0.0f, MAX_RADIUS_LIMIT), 0.0f, MAX_RADIUS_LIMIT) {
		for (std::uint32_t i = 0; i < Objects::Body::BODY_SEGMENTS; ++i) {
			heights_.push_back(Gene<float>(randFloat(0.0f, MAX_HEIGHT_LIMIT), 0.0f, MAX_HEIGHT_LIMIT));
		}
	}

	Genotype::Genotype(const Genotype & other) : Genotype()
	{
		front_radius_ = other.front_radius_;
		back_radius_ = other.back_radius_;
		heights_ = other.heights_;
		fitness = other.fitness;
	}

	Genotype& Genotype::operator=(const Genotype & other)
	{
		front_radius_ = other.front_radius_;
		back_radius_ = other.back_radius_;
		heights_.clear();
		heights_ = other.heights_;
		fitness = other.fitness;
		return *this;
	}

	void Genotype::mutate(float mutation_rate)
	{
		front_radius_.mutate(mutation_rate);
		back_radius_.mutate(mutation_rate);
		for (unsigned int i = 0; i < heights_.size(); ++i) {
			heights_[i].mutate(mutation_rate);
		}
	}

	Genotype Genotype::cross(const Genotype & other) const
	{
		Genotype child;
		child.front_radius_ = front_radius_.cross(other.front_radius_);
		child.back_radius_ = back_radius_.cross(other.back_radius_);
		child.heights_.clear();
		for (unsigned int i = 0; i < heights_.size(); ++i) {
			child.heights_.push_back(heights_[i].cross(other.heights_[i]));
		}
		return child;
	}

	Objects::Vehicle Genotype::generate(Objects::Vector2 position) const 
	{
		float front_wheel_r = front_radius_.value();
		float back_wheel_r = back_radius_.value();
		std::vector<float> heights_r;
		for (auto& h : heights_) {
			heights_r.push_back(h.value());
		}
		return Objects::Vehicle(position, heights_r, front_wheel_r, back_wheel_r);
	}
	float Genotype::randFloat(float min_value, float max_value) {
		std::uniform_real_distribution<float> random(min_value, max_value);
		float result = random(rng_);
		return result;
	}
	std::ostream& operator<< (std::ostream &stream, const Genotype &genotype) {
		/*stream << genotype.front_radius_ << " " << genotype.back_radius_ << " ";
		for (const auto& height : genotype.heights_) {
			stream << height << " ";
		}*/
		return stream;
	}
	std::istream& operator>> (std::istream & stream, Genotype& genotype) {
		/*stream >> genotype.front_radius_ >> genotype.back_radius_;
		for (std::uint32_t i = 0; i < Objects::Body::BODY_SEGMENTS; ++i) {
			std::uint32_t temp_value;
			stream >> temp_value;
			genotype.heights_.push_back(temp_value);
		}*/
		return stream;
	}
}