#include <galaxy-explorer/GameAI.hpp>
#include <galaxy-explorer/MyAIData.hpp>

#include <SFML/Graphics.hpp>


GameAI::GameAI(const GameInfo& game_info, sf::RenderTarget* debug_rt)
{
	this->debug_rt = debug_rt;
	this->game_info = game_info;
	this->asteroid_observer = AsteroidsObserver(this);
	this->my_game_ai = new MyAIData();

	// customState().debug_on = false;
}

GameAI::~GameAI() {
	delete my_game_ai;
}

SuggestedAction GameAI::suggestAction(const ShipState& ship_state) {
	debug_rt->clear(sf::Color::Transparent);
        
	if (customState().debug_on) {
		if (not asteroidsObserver().asteroids().isEmpty()) {
			const sf::IntRect first_ast_hb = asteroidsObserver().asteroids().front().getCurrentHitbox();
			sf::RectangleShape ast_rect(sf::Vector2f(first_ast_hb.width, first_ast_hb.height));
			ast_rect.setPosition(first_ast_hb.left, first_ast_hb.top);
			ast_rect.setOutlineThickness(33.0f); // if lines are too thin, they won't show up sometimes
			ast_rect.setOutlineColor(sf::Color::Yellow);
			ast_rect.setFillColor(sf::Color::Transparent);
			debug_rt->draw(ast_rect);
		}
	} 

	// return SimpleActions::NO_CHANGE;
        
        //if the Ship reaches rightmost angle, start turning CCW
	if(ship_state.millidegree_rotation>36000){
            my_game_ai->turnCW = 0;
        }    
        
        //if the Ship reaches leftmost angle, start turning CW
	else if(ship_state.millidegree_rotation<(-36000)){
            my_game_ai->turnCW = 1;
        }
        
        //No matter which direction the ship is turning in, it will always attempt to fire
        //if turnCW is true, yaw clockwise
        if(my_game_ai->turnCW == 1){
            return SuggestedAction{ SuggestedAction::YawingClockwise, SuggestedAction::FiringTry };
        }
        
        //otherwise turnCW should be false and the ship will jaw counterclockwise
        else if(my_game_ai->turnCW == 0){
            return SuggestedAction{ SuggestedAction::YawingAntiClockwise, SuggestedAction::FiringTry };
        }
}
