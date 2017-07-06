let component = ReasonReact.statelessComponent "App";

let make ::route _children => {
  ...component,
  render: fun _self => {
    let page =
      switch route {
      | Routing.Home => <TopStoriesPage />
      | Routing.Comments id => <CommentsPage id />
      };
    <div> page </div>
  }
};
