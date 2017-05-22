open Utils;

module App = {
  include ReactRe.Component;
  type props = {route: Routing.route};
  let name = "App";
  let render {props} => {
    let page =
      switch props.route {
      | Routing.Home => <TopStoriesPage />
      | Routing.Comments id => <CommentsPage id />
      };
    <div> page </div>
  };
};

include ReactRe.CreateComponent App;

let createElement ::route => wrapProps {route: route};
