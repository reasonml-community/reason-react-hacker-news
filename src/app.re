open Utils;

requireCSS "src/App.css";

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
    <div className="App">
      <div className="App_header">
        <a href="#/"> <h1> (ReactRe.stringToElement "Reason React Hacker News") </h1> </a>
      </div>
      page
    </div>
  };
};

include ReactRe.CreateComponent App;

let createElement ::route => wrapProps {route: route};
