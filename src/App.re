open Utils;

requireCSS("src/App.css");

type route =
  | Home
  | Comments(int)
  | NotFound;

type state = {route};

type action =
  | ChangeRoute(route);

let reducer = (action, _state) =>
  switch (action) {
  | ChangeRoute(route) => ReasonReact.Update({route: route})
  };

let mapUrlToRoute = (url: ReasonReact.Router.url) =>
  switch (url.path) {
  | [] => Home
  | ["comments", id] => Comments(int_of_string(id))
  | _ => NotFound
  };

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  reducer,
  initialState: () => {route: Home},
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url =>
          self.send(ChangeRoute(url |> mapUrlToRoute))
        ),
      ReasonReact.Router.unwatchUrl,
    ),
  ],
  render: self =>
    switch (self.state.route) {
    | Home => <TopStoriesPage />
    | Comments(id) => <CommentsPage id />
    | NotFound => <NotFound />
    },
};
